#include <iostream>
#include "GrahamScan.h"
#include "Utils_IO.h"
using namespace std;

#include <chrono>
#include <random>
using namespace std::chrono;

int main() {
	std::vector<int> v(1'000'000);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 1'000'000);
	for (int i = 0; i < 1'000'000; i++) {
		v[i] = dist(gen);
	}
	using clock = chrono::system_clock;
	auto start_time = clock::now();

	v = AVLTree<int>(v.begin(), v.end()).data();

	auto end_time = clock::now();
	cout << "time: " << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() << "ms\n";

	return 0;
}
