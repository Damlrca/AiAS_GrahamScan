#include "GrahamScan.h"
#include "AVLTree.h"
#include "QuickSort.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>

double cross_product(const Point& a, const Point& b) {
	return a.x * b.y - a.y * b.x;
}

struct PolarAngleComp {
	Point basePoint;
	PolarAngleComp(Point _basePoint) : basePoint{ _basePoint } {}
	bool operator()(const Point& a, const Point& b) {
		Point v1 = a - basePoint;
		Point v2 = b - basePoint;
		double crossprod = cross_product(v1, v2);
		if (crossprod > 0)
			return true;
		if (crossprod < 0)
			return false;
		double d1 = abs(v1.x) + abs(v1.y);
		double d2 = abs(v2.x) + abs(v2.y);
		return d1 < d2; // Manhattan distance is enough
	}
};

template<typename S>
std::vector<Point> _GrahamScan(const std::vector<Point>& a, S* sort) {
	if (a.empty())
		throw std::invalid_argument{ "empty vector of Points" };

	// basePoint
	Point basePoint = a.front();
	for (const auto& p : a)
		if (p.y < basePoint.y || (p.y == basePoint.y && p.x < basePoint.x))
			basePoint = p;

	// Sort by polar angle
	std::vector<Point> temp;
	for (const auto& p : a)
		if (p != basePoint)
			temp.push_back(p);
	sort(temp.begin(), temp.end(), PolarAngleComp{ basePoint });

	std::vector<Point> ans{ basePoint };

	// temp.size() == 0 or temp.size() == 1
	if (temp.size() <= 1) {
		for (auto& p : temp)
			ans.push_back(p);
		return ans;
	}
	
	// If several points are of the same angle delete all but the furthest point
	int temp_last_id = 0;
	for (int i = 1; i < temp.size(); i++) {
		if (cross_product(temp[i] - basePoint, temp[temp_last_id] - basePoint) != 0)
			temp_last_id++;
		temp[temp_last_id] = temp[i];
	}
	temp.resize(temp_last_id + 1);

	ans.push_back(temp[0]);
	ans.push_back(temp[1]);
	for (int i = 2; i < temp.size(); i++) {
		while (true) {
			Point v1 = ans.back() - ans[ans.size() - 2];
			Point v2 = temp[i] - ans.back();
			if (cross_product(v1, v2) > 0)
				break;
			ans.pop_back();
		}
		ans.push_back(temp[i]);
	}
	return ans;
}

std::vector<Point> GrahamScan_AVLTreeSort(const std::vector<Point>& a) {
	return _GrahamScan(a, AVLTreeSort<std::vector<Point>::iterator, PolarAngleComp>);
}

std::vector<Point> GrahamScan_AVLTreeSort_recursive(const std::vector<Point>& a) {
	return _GrahamScan(a, AVLTreeSort_recursive<std::vector<Point>::iterator, PolarAngleComp>);
}

std::vector<Point> GrahamScan_QuickSort(const std::vector<Point>& a) {
	return _GrahamScan(a, QuickSort<std::vector<Point>::iterator, PolarAngleComp>);
}
