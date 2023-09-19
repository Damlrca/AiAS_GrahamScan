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

void avl_sort(vector<long long>& v) {
	AVLTree<long long> tree;
	for (auto& i : v)
		tree.insert(i);
	v = tree.data();
}

void avl_sort_recursive(vector<long long>& v) {
	AVLTree<long long> tree;
	for (auto& i : v)
		tree.insert_recursive(i);
	v = tree.data();
}

int main() {
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<long long> dist(1, 1'000'000'000);
	using clock = chrono::system_clock;
	ofstream out;

	out.open("AVL_Iterative_Random.txt");
	for (int sz = 1; sz <= 1'000'001; sz += 10'000) {
		long long time = 0;
		int k = 10;
		while (k--) {
			vector<long long> v(sz);
			{
				for (auto& j : v)
					j = dist(gen);
			}
			vector<long long> t = v; sort(t.begin(), t.end());
			auto start_time = clock::now();
			avl_sort(v);
			auto end_time = clock::now();
			if (t != v) {
				out << "ERROR" << endl;
				return -1;
			}
			time += duration_cast<milliseconds>(end_time - start_time).count();
		}
		out << sz << " " << time / 10 << endl;
		cout << sz << endl;
	}
	cout << "AVL_Iterative_Random.txt" << endl;
	out.close();

	out.open("AVL_Iterative_Sorted.txt");
	for (int sz = 1; sz <= 1'000'001; sz += 10'000) {
		long long time = 0;
		int k = 10;
		while (k--) {
			vector<long long> v(sz);
			{
				for (auto& j : v)
					j = dist(gen);
				sort(v.begin(), v.end());
			}
			vector<long long> t = v; sort(t.begin(), t.end());
			auto start_time = clock::now();
			avl_sort(v);
			auto end_time = clock::now();
			if (t != v) {
				out << "ERROR" << endl;
				return -1;
			}
			time += duration_cast<milliseconds>(end_time - start_time).count();
		}
		out << sz << " " << time / 10 << endl;
		cout << sz << endl;
	}
	cout << "AVL_Iterative_Sorted.txt" << endl;
	out.close();

	out.open("AVL_Iterative_SortedReversed.txt");
	for (int sz = 1; sz <= 1'000'001; sz += 10'000) {
		long long time = 0;
		int k = 10;
		while (k--) {
			vector<long long> v(sz);
			{
				for (auto& j : v)
					j = dist(gen);
				sort(v.begin(), v.end());
				reverse(v.begin(), v.end());
			}
			vector<long long> t = v; sort(t.begin(), t.end());
			auto start_time = clock::now();
			avl_sort(v);
			auto end_time = clock::now();
			if (t != v) {
				out << "ERROR" << endl;
				return -1;
			}
			time += duration_cast<milliseconds>(end_time - start_time).count();
		}
		out << sz << " " << time / 10 << endl;
		cout << sz << endl;
	}
	cout << "AVL_Iterative_SortedReversed.txt" << endl;
	out.close();
	
	out.open("AVL_Recursive_Random.txt");
	for (int sz = 1; sz <= 1'000'001; sz += 10'000) {
		long long time = 0;
		int k = 10;
		while (k--) {
			vector<long long> v(sz);
			{
				for (auto& j : v)
					j = dist(gen);
			}
			vector<long long> t = v; sort(t.begin(), t.end());
			auto start_time = clock::now();
			avl_sort_recursive(v);
			auto end_time = clock::now();
			if (t != v) {
				out << "ERROR" << endl;
				return -1;
			}
			time += duration_cast<milliseconds>(end_time - start_time).count();
		}
		out << sz << " " << time / 10 << endl;
		cout << sz << endl;
	}
	cout << "AVL_Recursive_Random.txt" << endl;
	out.close();

	out.open("AVL_Recursive_Sorted.txt");
	for (int sz = 1; sz <= 1'000'001; sz += 10'000) {
		long long time = 0;
		int k = 10;
		while (k--) {
			vector<long long> v(sz);
			{
				for (auto& j : v)
					j = dist(gen);
				sort(v.begin(), v.end());
			}
			vector<long long> t = v; sort(t.begin(), t.end());
			auto start_time = clock::now();
			avl_sort_recursive(v);
			auto end_time = clock::now();
			if (t != v) {
				out << "ERROR" << endl;
				return -1;
			}
			time += duration_cast<milliseconds>(end_time - start_time).count();
		}
		out << sz << " " << time / 10 << endl;
		cout << sz << endl;
	}
	cout << "AVL_Recursive_Sorted.txt" << endl;
	out.close();

	out.open("AVL_Recursive_SortedReversed.txt");
	for (int sz = 1; sz <= 1'000'001; sz += 10'000) {
		long long time = 0;
		int k = 10;
		while (k--) {
			vector<long long> v(sz);
			{
				for (auto& j : v)
					j = dist(gen);
				sort(v.begin(), v.end());
				reverse(v.begin(), v.end());
			}
			vector<long long> t = v; sort(t.begin(), t.end());
			auto start_time = clock::now();
			avl_sort_recursive(v);
			auto end_time = clock::now();
			if (t != v) {
				out << "ERROR" << endl;
				return -1;
			}
			time += duration_cast<milliseconds>(end_time - start_time).count();
		}
		out << sz << " " << time / 10 << endl;
		cout << sz << endl;
	}
	cout << "AVL_Recursive_SortedReversed.txt" << endl;
	out.close();
	
	return 0;
}
