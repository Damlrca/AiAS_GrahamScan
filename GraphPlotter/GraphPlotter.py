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
    ### AVLTree Iteratrive
    files = ["TS_AVLTree_ll_random.txt", "TS_AVLTree_ll_sorted.txt", "TS_AVLTree_ll_reversed.txt"]
    nameLines = ["Random", "Sorted", "SortedReversed"]
    nameGraph = "Sort by AVLTree, vector<long long>, iterative"

    ### AVLTree Recursive
    # files = ["TS_AVLTreeRecursive_ll_random.txt", "TS_AVLTreeRecursive_ll_sorted.txt", "TS_AVLTreeRecursive_ll_reversed.txt"]
    # nameLines = ["Random", "Sorted", "SortedReversed"]
    # nameGraph = "Sort by AVLTree, vector<long long>, recursive"

    ### QuickSort
    # files = ["TS_QuickSort_ll_random.txt", "TS_QuickSort_ll_sorted.txt", "TS_QuickSort_ll_reversed.txt"]
    # nameLines = ["Random", "Sorted", "SortedReversed"]
    # nameGraph = "QuickSort, vector<long long>"

    ### AVLTree Compare Iteratrive and Recursive
    # files = ["TS_AVLTree_ll_random.txt", "TS_AVLTree_ll_sorted.txt", "TS_AVLTree_ll_reversed.txt",
    #          "TS_AVLTreeRecursive_ll_random.txt", "TS_AVLTreeRecursive_ll_sorted.txt", "TS_AVLTreeRecursive_ll_reversed.txt"]
    # nameLines = ["iterative_Random", "iterative_Sorted", "iterative_SortedReversed",
    #              "recursive_Random", "recursive_Sorted", "recursive_SortedReversed"]
    # nameGraph = "Sort by AVLTree, vector<long long>"

    ### Graham Scan E1
    # files = ["GS_E1_A_AVLTree.txt", "GS_E1_B_AVLTree.txt",
    #          "GS_E1_A_AVLTreeRecursive.txt", "GS_E1_B_AVLTreeRecursive.txt",
    #          "GS_E1_A_QuickSort.txt", "GS_E1_B_QuickSort.txt"]
    # nameLines = ["E1_A_AVLTree", "E1_B_AVLTree",
    #              "E1_A_AVLTreeRecursive", "E1_B_AVLTreeRecursive",
    #              "E1_A_QuickSort", "E1_B_QuickSort"]
    # nameGraph = "Graham Scan E1"

    ### Graham Scan E2
    # files = ["GS_E2_A_AVLTree.txt", "GS_E2_B_AVLTree.txt",
    #          "GS_E2_A_AVLTreeRecursive.txt", "GS_E2_B_AVLTreeRecursive.txt",
    #          "GS_E2_A_QuickSort.txt", "GS_E2_B_QuickSort.txt"]
    # nameLines = ["E2_A_AVLTree", "E2_B_AVLTree",
    #              "E2_A_AVLTreeRecursive", "E2_B_AVLTreeRecursive",
    #              "E2_A_QuickSort", "E2_B_QuickSort"]
    # nameGraph = "Graham Scan E2"

    dataArrays = readDataFiles(files)
    nameX = "Size of array"
    # for Graham Scan E2:
    # nameX = "Width of rectangle"
    nameY = "Time (ms)"

    fig = plt.figure(figsize=(7 * 1.5, 4 * 1.5))
    ax = fig.add_subplot()
    setConfig(fig, ax, nameGraph, nameX, nameY)

    for index, data in enumerate(dataArrays):
        plt.plot(data[0], data[1], label=nameLines[index])
        # for AVLTree Compare:
        # plt.plot(data[0], data[1], label=nameLines[index], color=('darkblue', 'darkorange')[index >= 3])

    plt.legend()
    plt.grid()
    plt.show()
