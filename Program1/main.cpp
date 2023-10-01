#include <iostream>
#include "GrahamScan.h"
#include "Utils_IO.h"
#include <fstream>
#include <chrono>
using myclock = std::chrono::system_clock;

// For example:
// /Program1/Input.txt
// /Program1/Output.txt

int main() {
	auto v = readFile("Input.txt");
	myclock::time_point start_time, end_time;
	start_time = myclock::now();
	v = GrahamScan_AVLTreeSort(v);
	// v = GrahamScan_AVLTreeSort_recursive(v);
	// v = GrahamScan_QuickSort(v);
	end_time = myclock::now();
	int time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
	saveFile("Output.txt", v, time_ms);
	return 0;
}
