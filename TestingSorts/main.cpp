#include "AVLTree.h"
#include "QuickSort.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>
using namespace std;
using namespace std::chrono;

std::random_device rd;
std::mt19937_64 gen(rd());
std::uniform_int_distribution<long long> dist(1, 1'000'000'000);

using myclock = chrono::system_clock;

enum class SortType {
	AVL, AVL_recursive, Quick
};

enum class TestType {
	Random, Sorted, Reversed
};

void test_sort_ll(const char* filename, TestType tt, SortType st) {
	ofstream out(filename);
	for (int sz = 1; sz <= 1'000'001; sz += 10'000) {
		long long time = 0;
		int k = 10;
		while (k--) {
			// generate v
			vector<long long> v(sz);
			switch (tt) {
			case TestType::Random:
				for (auto& j : v)
					j = dist(gen);
				break;
			case TestType::Sorted:
				iota(v.begin(), v.end(), 0ll);
				break;
			case TestType::Reversed:
				iota(v.begin(), v.end(), 0ll);
				reverse(v.begin(), v.end());
				break;
			default:
				break;
			}
			// t
			vector<long long> t = v; sort(t.begin(), t.end());
			// sort
			myclock::time_point start_time, end_time;
			switch (st) {
			case SortType::AVL:
				start_time = myclock::now();
				AVLTreeSort(v.begin(), v.end());
				end_time = myclock::now();
				break;
			case SortType::AVL_recursive:
				start_time = myclock::now();
				AVLTreeSort_recursive(v.begin(), v.end());
				end_time = myclock::now();
				break;
			case SortType::Quick:
				start_time = myclock::now();
				QuickSort(v.begin(), v.end());
				end_time = myclock::now();
				break;
			default:
				break;
			}
			// check
			if (t != v) {
				out << "ERROR" << endl;
				exit(-1);
			}
			time += duration_cast<milliseconds>(end_time - start_time).count();
		}
		out << sz << " " << time / 10 << endl;
		cout << sz << endl;
	}
}

int main() {
	test_sort_ll("TS_AVLTree_ll_random.txt", TestType::Random, SortType::AVL);
	test_sort_ll("TS_AVLTree_ll_sorted.txt", TestType::Sorted, SortType::AVL);
	test_sort_ll("TS_AVLTree_ll_reversed.txt", TestType::Reversed, SortType::AVL);
	test_sort_ll("TS_AVLTreeRecursive_ll_random.txt", TestType::Random, SortType::AVL_recursive);
	test_sort_ll("TS_AVLTreeRecursive_ll_sorted.txt", TestType::Sorted, SortType::AVL_recursive);
	test_sort_ll("TS_AVLTreeRecursive_ll_reversed.txt", TestType::Reversed, SortType::AVL_recursive);
	test_sort_ll("TS_QuickSort_ll_random.txt", TestType::Random, SortType::Quick);
	test_sort_ll("TS_QuickSort_ll_sorted.txt", TestType::Sorted, SortType::Quick);
	test_sort_ll("TS_QuickSort_ll_reversed.txt", TestType::Reversed, SortType::Quick);
	return 0;
}
