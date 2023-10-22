#ifndef EDGE_HPP
#define EDGE_HPP

struct __edge {
    using ID = unsigned int;

    ID source;
    ID target;

    __edge(ID source, ID target) 
    : source(source), target(target) {}
};

#endif