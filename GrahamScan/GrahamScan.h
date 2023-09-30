#ifndef AiAS_GrahamScan
#define AiAS_GrahamScan
#include <vector>
#include "Utils.h"

std::vector<Point> GrahamScan_AVLTreeSort(const std::vector<Point>& a);

std::vector<Point> GrahamScan_AVLTreeSort_recursive(const std::vector<Point>& a);

std::vector<Point> GrahamScan_QuickSort(const std::vector<Point>& a);

#endif // !AiAS_GrahamScan
