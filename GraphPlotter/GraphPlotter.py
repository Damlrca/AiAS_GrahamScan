# to install matplotlib:
# pip install matplotlib
# to run:
# python GraphPlotter.py

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import NullLocator


def readDataFiles(filesArray):
    dataArrays = []
    for file in filesArray:
        with open(file, "r") as f:
            lines = f.readlines()
        x = []
        y = []
        for line in lines:
            elems = line.split()
            x.append(int(elems[0]))
            y.append(int(elems[1]))
        dataArrays.append((x, y))
    return dataArrays


def setConfig(fig, ax, nameGraph, nameX, nameY):
    fig.suptitle(nameGraph)
    ax.set_xlabel(nameX)
    ax.set_ylabel(nameY)


if __name__ == "__main__":
    ### Experiment 1
    files = ["GS_E1_A_AVLTreeRecursive.txt", "GS_E1_B_AVLTreeRecursive.txt",
             "GS_E1_A_QuickSort.txt", "GS_E1_B_QuickSort.txt"]
    nameLines = ["AVLTree $T_A(n)$", "AVLTree $T_B(n)$",
                 "QuickSort $T_A(n)$", "QuickSort $T_B(n)$"]
    nameGraph = "Experiment 1"
    nameX = "n = size of array A"
    nameY = "Time(ms)"

    ### Experiment 2
    # files = ["GS_E2_A_AVLTreeRecursive.txt", "GS_E2_B_AVLTreeRecursive.txt",
    #          "GS_E2_A_QuickSort.txt", "GS_E2_B_QuickSort.txt"]
    # nameLines = ["AVLTree $T_A(q)$", "AVLTree $T_B(q)$",
    #              "QuickSort $T_A(q)$", "QuickSort $T_B(q)$"]
    # nameGraph = "Experiment 2"
    # nameX = "q = side of the square"
    # nameY = "Time (ms)"

    dataArrays = readDataFiles(files)

    fig = plt.figure(figsize=(7.5, 4))
    ax = fig.add_subplot()
    setConfig(fig, ax, nameGraph, nameX, nameY)

    for index, data in enumerate(dataArrays):
        # plt.plot(data[0], data[1], label=nameLines[index])
        plt.plot(data[0], data[1], label=nameLines[index],
                 color=['purple', 'orangered', 'mediumblue', 'limegreen'][index])

    plt.legend()
    plt.grid()
    plt.show()
