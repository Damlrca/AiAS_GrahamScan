#include "GrahamScan.h"
#include "AVLTree.h"
#include "QuickSort.h"
#include <algorithm>
#include <cmath>

struct PolarAngleComp {
	Point basePoint;
	PolarAngleComp(Point _basePoint) : basePoint{ _basePoint } {}
	bool operator()(const Point& a, const Point& b) {
		Point v1{ a.x - basePoint.x, a.y - basePoint.y };
		Point v2{ b.x - basePoint.x, b.y - basePoint.y };
		double crossprod = v1.x * v2.y - v1.y * v2.x;
		if (crossprod > 0)
			return true;
		if (crossprod < 0)
			return false;
		double d1 = abs(v1.x) + abs(v1.y);
		double d2 = abs(v2.x) + abs(v2.y);
		return d1 < d2;
	}
};

template<typename S>
std::vector<Point> _GrahamScan(const std::vector<Point>& a, S* sort) {
	if (a.empty())
		throw std::exception{ "empty vector of Points" };

	Point basePoint = a.front();
	for (const auto& p : a)
		if (p.y < basePoint.y || (p.y == basePoint.y && p.x < basePoint.x))
			basePoint = p;

	std::vector<Point> temp;
	for (const auto& p : a)
		if (p != basePoint)
			temp.push_back(p);
	sort(temp.begin(), temp.end(), PolarAngleComp{basePoint});
	std::unique(temp.begin(), temp.end());

	return temp;
}

std::vector<Point> GrahamScan_AVLTreeSort(const std::vector<Point>& a) {
	return _GrahamScan(a, AVLTreeSort<std::vector<Point>::iterator, PolarAngleComp>);
}

std::vector<Point> GrahamScan_QuickSort(const std::vector<Point>& a) {
	return _GrahamScan(a, QuickSort<std::vector<Point>::iterator, PolarAngleComp>);
}
