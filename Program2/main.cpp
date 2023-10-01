#include <iostream>
#include <chrono>
#include "GrahamScan.h"
#include "Utils_IO.h"
#include "Utils_TestGen.h"
using namespace std;
using namespace std::chrono;

using myclock = chrono::system_clock;

enum class GrahamScanVariant {
	AVL, AVL_recursive, QuickSort
};

enum class GenTestType {
	A, B
};

enum class ExperimentType {
	E1, E2
};

void test_GrahamScan(std::string filename, ExperimentType et, GenTestType gtt, GrahamScanVariant gsv) {
	vector<pair<int, int>> results;
	for (int i = 0; i <= 1'000'000; i += 10'000) {
		int n, q, w;
		switch (et)
		{
		case ExperimentType::E1:
			n = i + 1;
			q = w = 1'000'000;
			break;
		case ExperimentType::E2:
			n = 1'000'000;
			q = w = i;
			break;
		default:
			break;
		}
		int k = 10;
		int time = 0;
		while (k--) {
			// generate test
			vector<Point> test;
			switch (gtt) {
			case GenTestType::A:
				test = genTest_TypeA(n, q, w);
				break;
			case GenTestType::B:
				test = genTest_TypeB(n, q, w);
				break;
			default:
				break;
			}
			// GrahamScan
			myclock::time_point start_time, end_time;
			vector<Point> v;
			switch (gsv) {
			case GrahamScanVariant::AVL:
				start_time = myclock::now();
				v = GrahamScan_AVLTreeSort(test);
				end_time = myclock::now();
				break;
			case GrahamScanVariant::AVL_recursive:
				start_time = myclock::now();
				v = GrahamScan_AVLTreeSort_recursive(test);
				end_time = myclock::now();
				break;
			case GrahamScanVariant::QuickSort:
				start_time = myclock::now();
				v = GrahamScan_QuickSort(test);
				end_time = myclock::now();
				break;
			default:
				break;
			}
			time += duration_cast<milliseconds>(end_time - start_time).count();
		}
		cout << filename << " " << n << " " << time / 10 << endl;
		results.push_back({ n, time / 10 });
	}
	saveTestsResults(filename, results);
}

int main() {
	test_GrahamScan("GS_E1_A_AVLTree.txt", ExperimentType::E1, GenTestType::A, GrahamScanVariant::AVL);
	test_GrahamScan("GS_E1_B_AVLTree.txt", ExperimentType::E1, GenTestType::B, GrahamScanVariant::AVL);
	test_GrahamScan("GS_E2_A_AVLTree.txt", ExperimentType::E2, GenTestType::A, GrahamScanVariant::AVL);
	test_GrahamScan("GS_E2_B_AVLTree.txt", ExperimentType::E2, GenTestType::B, GrahamScanVariant::AVL);
	test_GrahamScan("GS_E1_A_AVLTreeRecursive.txt", ExperimentType::E1, GenTestType::A, GrahamScanVariant::AVL_recursive);
	test_GrahamScan("GS_E1_B_AVLTreeRecursive.txt", ExperimentType::E1, GenTestType::B, GrahamScanVariant::AVL_recursive);
	test_GrahamScan("GS_E2_A_AVLTreeRecursive.txt", ExperimentType::E2, GenTestType::A, GrahamScanVariant::AVL_recursive);
	test_GrahamScan("GS_E2_B_AVLTreeRecursive.txt", ExperimentType::E2, GenTestType::B, GrahamScanVariant::AVL_recursive);
	test_GrahamScan("GS_E1_A_QuickSort.txt", ExperimentType::E1, GenTestType::A, GrahamScanVariant::QuickSort);
	test_GrahamScan("GS_E1_B_QuickSort.txt", ExperimentType::E1, GenTestType::B, GrahamScanVariant::QuickSort);
	test_GrahamScan("GS_E2_A_QuickSort.txt", ExperimentType::E2, GenTestType::A, GrahamScanVariant::QuickSort);
	test_GrahamScan("GS_E2_B_QuickSort.txt", ExperimentType::E2, GenTestType::B, GrahamScanVariant::QuickSort);
	return 0;
}
