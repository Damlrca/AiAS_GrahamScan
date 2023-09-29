#include "GrahamScan.h"
#include "AVLTree.h"
#include "QuickSort.h"

// TODO RENAME ???
struct PointAngleComp {
	Point basePoint;
	PointAngleComp(Point _basePoint) : basePoint{ _basePoint } {}
	bool operator()(const Point& a, const Point& b) {
		// TODO this realization just for test
		if (a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	}
};

template<typename S>
std::vector<Point> _GrahamScan(std::vector<Point> a, S* sort) {
	// TODO
	Point basePoint = { 0, 0 };
	sort(a.begin(), a.end(), PointAngleComp{basePoint});
	return a;
}

std::vector<Point> GrahamScan_AVLTreeSort(const std::vector<Point>& a) {
	return _GrahamScan(a, AVLTreeSort<std::vector<Point>::iterator, PointAngleComp>);
}

std::vector<Point> GrahamScan_QuickSort(const std::vector<Point>& a) {
	return _GrahamScan(a, QuickSort<std::vector<Point>::iterator, PointAngleComp>);
}
