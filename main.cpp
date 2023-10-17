#include <vector>
#include <deque>
#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <fstream>
#include <string>

const int BETRAY    = 0;
const int COOPERATE = 1;
const int TFT       = 2;

const int STRATEGY_COUNT = 2;

std::mt19937 mt(time(NULL));  
std::uniform_int_distribution<int> dist(0, 100); 
// 均匀取0~100随机数 
inline size_t get_random() {
    return dist(mt);
}

struct node {
    // 用deque是因为节点之间的连接使用地址，为了使地址固定和随机访问的便利而使用deque
    std::vector<node*> neighbors;
    struct {
        double payoff = 0;
        int strategy  = -1;
        double this_tern_payoff = 0;
    } data;

    node(int strategy) { data.strategy = strategy; }
    bool operator==(const node& x) { return this == &x; }
    void connect(node* x) {
        neighbors.push_back(x);
        x->neighbors.push_back(this);
    }
};

class network {
public:
    std::deque<node> nodes;
    struct {
        double betray_ok_payoff = 0;
        double rationality = 0;
    } factor;
    size_t init_node_count = 2;

    network(size_t init_node_count, double betray_ok_payoff) {
        factor.betray_ok_payoff = betray_ok_payoff;
        for (size_t i = 0; i < init_node_count; i++) {
            add_node();
        }   
        init_node_connect(); 
    }

    // 把边加node边迭代
    void gambling(size_t iterate_count) {
        for (size_t i = 0; i < iterate_count; i++) {
            add_node();
            new_node_connect();
            caculate();
            opitimize();
        }
    }

    void init(size_t init_node_count) {
        for (size_t i = 0; i < init_node_count; i++) {
            add_node();
            new_node_connect();
        }
    }    

    void run(size_t iterate_count) {
        for (size_t i = 0; i < iterate_count; i++) {
            caculate();
            opitimize();
        }
    }


    double cooperation_density() {
        double sum = 0;
        for (auto i : nodes)
            sum += i.data.strategy;
        return sum / nodes.size();
    }

    double total_revenue() {
        double sum = 0;
        for (auto i : nodes)
            sum += i.data.payoff;
        return sum;
    }

private:
    // 网络度数总和
    size_t degrees_sum() {
        size_t sum = 0;
        for (auto i : nodes)
            sum += i.neighbors.size();
        return sum;
    }

    // 网络添加节点
    void add_node() {
        nodes.push_back(node(get_random() % STRATEGY_COUNT));
    }

    // 初始化网络节点
    void init_node_connect() {
        // 初始点相互连接
        for (size_t i = 0; i < nodes.size(); i++) {
            for (size_t j = i+1; j < nodes.size(); j++) {
                nodes[i].connect(&nodes[j]);
            }
        }
    }

    void new_node_connect() {
        do {
            std::vector<size_t> connect_who;
            for (size_t i = 0; i < nodes.size()-1; i++) {
                double rand = get_random() / (double) 100;
                double p = nodes[i].neighbors.size() / (double) degrees_sum();
                if (p > rand)
                    connect_who.push_back(i);
            }
            for (auto i : connect_who)
                nodes[nodes.size()-1].connect(&nodes[i]);
        // 如果新加的节点一个都没连接到就重新尝试
        } while (nodes[nodes.size()-1].neighbors.size() == 0);
    }

    void caculate() {
        // 记录本轮收益
        double this_tern_payoff[nodes.size()];
        for (auto &i : this_tern_payoff)
            i = 0;
        // 记录本轮谁和谁战斗过
        std::vector<size_t> battled_table[nodes.size()];

        for (size_t i = 0; i < nodes.size(); i++) {
            for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
                // 先找到该邻居在nodes中的下标
                auto offset = std::find(nodes.begin(), nodes.end(), *nodes[i].neighbors[j]);
                size_t index = offset - nodes.begin();
                // 如果博弈过了就跳过
                if (std::find(battled_table[i].begin(), battled_table[i].end(), index) != battled_table[i].end())
                    continue;
                // 博弈记录到表中
                battled_table[i].push_back(index);
                battled_table[index].push_back(i);
                
                battle(i, index, this_tern_payoff);
            }
        }
        // 更新收益
        for (size_t i = 0; i < nodes.size(); i++) {
            // 总收益
            nodes[i].data.payoff += this_tern_payoff[i];
            // 记录本回合收益
            nodes[i].data.this_tern_payoff = this_tern_payoff[i];
        }
    }

    void opitimize() {
        // 本回合策略，初始化为-1表示不更改策略
        int this_tern_strategy[nodes.size()];
        for (auto &i : this_tern_strategy)
            i = -1;

        // 优化每个节点
        for (size_t i = 0; i < nodes.size(); i++) {
            // 先遍历节点的邻居，找出要学习的节点，度越大的节点选择到的概率越大
            double degrees_table[nodes[i].neighbors.size()];
            size_t neighbors_degrees_sum = 0;
            for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
                size_t temp = nodes[i].neighbors[j]->neighbors.size();
                neighbors_degrees_sum += temp;
                degrees_table[j] = temp;
            }

            // 使degrees_table的总和为1
            for (auto &j : degrees_table)
                j /= neighbors_degrees_sum;
            
            double rand = get_random() / (double) 100;
            size_t find = 0;
            for (; find < nodes[i].neighbors.size(); find++) {
                rand -= degrees_table[find];
                // rand精细度是小数点后两位，所以 rand<0.01 等价于 rand==0
                if (rand < 0.01)
                    break;
            }
            if (nodes[i].data.strategy == nodes[i].neighbors[find]->data.strategy)
                continue;
            // find为要学习的节点的下标，计算是否学习
            double p = 1 / (1 + exp((nodes[i].data.this_tern_payoff - nodes[i].neighbors[find]->data.this_tern_payoff) / 0.01));
            rand = get_random() / (double) 100;
            if (p > rand)
                this_tern_strategy[i] = nodes[i].neighbors[find]->data.strategy;
        }
        // 更新本回的策略
        for (size_t i = 0; i < nodes.size(); i++) {
            if (this_tern_strategy[i] == -1)
                continue;
            nodes[i].data.strategy = this_tern_strategy[i];
        }
    }

    // i, j 为nodes的下标，payoff为本回合的收益，battled为本次迭代战斗记录
    void battle(size_t i, size_t j, double* payoff) {
        if (nodes[i].data.strategy == nodes[j].data.strategy) {
            if (nodes[i].data.strategy == COOPERATE) {
                // 默认合作收益为1单位
                payoff[i] += 1;
                payoff[j] += 1;
            }
        }
        else {
            // 被背叛收益为0，背叛成功收益自定
            if (nodes[i].data.strategy == BETRAY) {
                payoff[i] += 1 + factor.betray_ok_payoff; 
                payoff[j] += 1 - factor.betray_ok_payoff;
            }
            else {
                payoff[j] += 1 + factor.betray_ok_payoff; 
                payoff[i] += 1 - factor.betray_ok_payoff;
            }
        }
    }


};




int main() {
    std::ofstream file("data.csv", std::ios::out);
    const size_t iteration_count = 200;
    const size_t init_node_count = 2;   

    file << "cooperation density,total revenue\n";
    
    for (double r = 0; r < 1; r += 0.05) {
        network x(init_node_count, r);
        x.init(198);
        x.run(100);
        file << x.cooperation_density() << "," << x.total_revenue() << "\n";
    }
    
    file.close();
}