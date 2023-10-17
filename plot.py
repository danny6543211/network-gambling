import matplotlib.pyplot as plt
import csv
import numpy as np


if __name__ == "__main__":
    reader = csv.reader(open("data.csv"))
    title = next(reader)

    # x
    x = [np.arange(0, 1, 0.05)]
    # y (str类型)
    __cooperation_desity = []
    __total_revenue = []

    # load y
    for row in reader:
        __cooperation_desity.append(row[0])
        __total_revenue.append(row[1])

    # y (double类型)
    cooperation_desity = [float(x) for x in __cooperation_desity]
    total_revenue = [float(x) for x in __total_revenue]

    plt.figure(figsize=(10, 8))

    plt.subplot(2, 1, 1)
    plt.xlabel("r")
    plt.ylabel("cooperation desity")
    plt.scatter(x, cooperation_desity)
    # plt.title("cooperation desity / r")

    plt.subplot(2, 1, 2)
    plt.xlabel("cooperation desity")
    plt.ylabel("total revenue")
    plt.scatter(cooperation_desity, total_revenue)
    # plt.title("cooperation desity / total revenue")

    plt.show()
