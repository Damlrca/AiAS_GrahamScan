#include "Utils_TestGen.h"
#include <random>
#include <iostream>
std::random_device rd;
std::mt19937_64 gen(rd());

std::vector<Point> genTest_TypeA(int n, int q, int w) {
	std::uniform_real_distribution<double> randX(0.0, double(q));
	std::uniform_real_distribution<double> randY(0.0, double(w));
	std::vector<Point> ret;
	for (int i = 0; i < n; i++)
		ret.push_back(Point{ randX(gen), randY(gen) });
	return ret;
}

std::vector<Point> genTest_TypeB(int n, int q, int w) {
	std::uniform_real_distribution<double> rand(0.0, double(2 * q + 2 * w));
	std::vector<Point> ret;
	for (int i = 0; i < n; i++) {
		double t = rand(gen);
		if (t <= q)
			ret.push_back(Point{ t, 0.0 });
		else if (t <= q + w)
			ret.push_back(Point{ double(q), t - q });
		else if (t <= 2 * q + w)
			ret.push_back(Point{ double(q) - (t - (q + w)),double(w) });
		else
			ret.push_back(Point{ 0.0, w - (t - (2 * q + w)) });
	}
	return ret;
}
