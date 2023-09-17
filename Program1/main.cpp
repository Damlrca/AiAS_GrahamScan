#include <iostream>
#include "GrahamScan.h"
#include "Utils_IO.h"

#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>
using namespace std;
using namespace std::chrono;

int main() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 1'000'000);
	using clock = chrono::system_clock;

	ofstream out("TestRandom.txt");
	for (int i = 1; i <= 1'000'001; i += 10'000) {
		vector<int> v(i);
		for (auto& j : v)
			j = dist(gen);
		long long time = 0;
		int k = 10;
		while (k--) {
			for (auto& j : v)
				j = dist(gen);
			auto start_time = clock::now();
			AVLTree<int>(v.begin(), v.end()).data();
			auto end_time = clock::now();
			time += duration_cast<milliseconds>(end_time - start_time).count();
		}
		out << i << " " << time / 10 << endl;
		cout << i << "\n";
	}
	cout << "cringe completed" << endl;
	return 0;
}
