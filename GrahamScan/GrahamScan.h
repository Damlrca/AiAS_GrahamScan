#ifndef AiAS_GrahamScan
#define AiAS_GrahamScan
#include <vector>

struct Point {
	double x;
	double y;
};
bool operator==(const Point& a, const Point& b);
bool operator!=(const Point& a, const Point& b);
Point operator-(const Point& a, const Point& b);
Point operator+(const Point& a, const Point& b);

std::vector<Point> GrahamScan_AVLTreeSort(const std::vector<Point>& a);

std::vector<Point> GrahamScan_AVLTreeSort_recursive(const std::vector<Point>& a);

std::vector<Point> GrahamScan_QuickSort(const std::vector<Point>& a);

#endif // !AiAS_GrahamScan
