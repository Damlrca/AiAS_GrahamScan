#include "Utils_IO.h"
#include <fstream>

std::vector<Point> readFile(std::string filename) {
	std::ifstream in(filename);
	int sz;
	in >> sz;
	std::vector<Point> res;
	for (int i = 0; i < sz; i++) {
		double x, y;
		in >> x >> y;
		res.push_back(Point{ x, y });
	}
	return res;
}

void saveFile(std::string filename, std::vector<Point> result, int time_ms) {
	std::ofstream out(filename);
	out << result.size() << std::endl;
	for (const auto& p : result)
		out << p.x << " " << p.y << std::endl;
	out << time_ms << std::endl;
}

void saveTestsResults(std::string filename, std::vector<std::pair<long long, long long>> results) {
	std::ofstream out(filename);
	for (const auto& t : results)
		out << t.first << " " << t.second << std::endl;
}
