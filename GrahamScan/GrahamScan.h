#ifndef AiAS_GrahamScan
#define AiAS_GrahamScan
#include <vector>

struct Point {
	double x;
	double y;
};

inline bool operator==(const Point& a, const Point& b) {
	return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const Point& a, const Point& b) {
	return !(a == b);
}

std::vector<Point> GrahamScan_AVLTreeSort(const std::vector<Point>& a);

std::vector<Point> GrahamScan_QuickSort(const std::vector<Point>& a);

#endif // !AiAS_GrahamScan
