import matplotlib.pyplot as plt
import csv
import numpy as np


if __name__ == "__main__":
    reader = csv.reader(open("test.csv"))

    # str y
    __y = []
    for row in reader:
        __y.append(row[0])
    # int y
    _y = [int(i) for i in __y]

    x = (np.arange(0, max(_y)+1, 1))

    y = [0 for i in range(x.size)]
    for i in _y:
        y[i-1] += 1

    print(y)

    plt.scatter(x, y)
    plt.show()