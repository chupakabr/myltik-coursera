/*

This file contains all of the 100,000 integers between 1 and 100,000 (inclusive) in some random order, with no integer repeated.

Your task is to compute the number of inversions in the file given, where the ith row of the file indicates the ith entry of an array.
Because of the large size of this array, you should implement the fast divide-and-conquer algorithm covered in the video lectures. The numeric answer for the given input file should be typed in the space below.
So if your answer is 1198233847, then just type 1198233847 in the space provided without any space / commas / any other punctuation marks. You can make up to 5 attempts, and we'll use the best one for grading.
(We do not require you to submit your code, so feel free to use any programming language you want --- just type the final numeric answer in the following space.)

[Tip: before submitting, first test the correctness of your program on some small test files or your own devising.]

*/


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


#define INPUT_FILE "IntegerArray.txt"

using namespace std;


typedef long val_t;
typedef long inv_t;
typedef vector<val_t> data_arr;


#define SPLIT_VECTOR(data_,a_,b_) \
	do { \
		if (data_.size() > 1) { \
			copy(data_.begin(), data_.begin()+(int)data_.size()/2, a_.begin()); \
			copy(data_.begin()+(int)data_.size()/2, data_.end(), b_.begin()); \
		} \
	} while (0);

/**
 * Echo array value
 */
void echo_val(val_t v)
{
	cout << v << ", ";
}

/**
 * Echo vector
 */
void echo_arr(data_arr v, string nm = "Vector: ")
{
	cout << nm;
	for_each(v.begin(), v.end(), echo_val);
	cout << endl;
}

/**
 * Merge arrays
 */
data_arr merge_data(data_arr& in_a, data_arr& in_b, inv_t &inversions_count)
{
	data_arr a, b;
	
	// Sort a
	if (in_a.size() > 1) {
		size_t sz = in_a.size();
		data_arr tmp_a(sz/2), tmp_b(sz-sz/2);
		SPLIT_VECTOR(in_a, tmp_a, tmp_b);
		a = merge_data(tmp_a, tmp_b, inversions_count);
	}
	else {
		a = in_a;
	}
	
	// Sort b
	if (in_b.size() > 1) {
		size_t sz = in_b.size();
		data_arr tmp_a(sz/2), tmp_b(sz-sz/2);
		SPLIT_VECTOR(in_b, tmp_a, tmp_b);
		b = merge_data(tmp_a, tmp_b, inversions_count);
	}
	else {
		b = in_b;
	}
	
	// Merge
	data_arr result;
	data_arr::iterator it_a = a.begin();
	data_arr::iterator it_b = b.begin();
	val_t erased_b_count = b.size();
	while (it_a != a.end() && it_b != b.end() && a.size() > 0 && b.size() > 0) {
		if (*it_b <= *it_a) {
			result.push_back(*it_b);
			it_b = b.erase(it_b);
			
			inversions_count += a.size();
		}
		else {
			result.push_back(*it_a);
			it_a = a.erase(it_a);
		}
	}
	
	// Finish merging
	if (a.size() > 0) {
		result.insert(result.end(), a.begin(), a.end());
	}
	if (b.size() > 0) {
		result.insert(result.end(), b.begin(), b.end());
	}
	
	return result;
}

/**
 * Count inversion merge function
 */
data_arr count_inversions(data_arr& data, inv_t &inversions_count)
{
	size_t sz = data.size();
	data_arr a(sz/2), b(sz-sz/2);
	
	SPLIT_VECTOR(data, a, b);
	echo_arr(a, "initial a: ");
	echo_arr(b, "initial b: ");
	data_arr result = merge_data(a, b, inversions_count);
	
	return result;
}

/**
 * Run test for specified vector
 */
void run_test(data_arr &v, short testNum, const val_t expected)
{
	// Initial
	cout << endl << "Running test#" << testNum << "..." << endl;
	cout << "Items count: " << v.size() << endl;
	
	// Merge Sort
	inv_t inversions_count = 0;
	data_arr result = count_inversions(v, inversions_count);
	
	// Results echo
	echo_arr(v, "Initial vector: ");
	echo_arr(result, "Result vector: ");
	
	cout << "Items count after sort: " << result.size() << endl;
	cout << "Number of inversions: " << inversions_count << " vs " << expected << endl;
	if (inversions_count != expected)
		cout << "ERROR Invalid evaluation!" << endl;
}


/**
 * MergeSort test
 */
int main()
{
	// Test data 1, expected: 1
	// 5-2
	data_arr data1;
	data1.push_back(1);
	data1.push_back(5);
	data1.push_back(2);
	run_test(data1, 1, 1);

	// Test data 2, expected: 3
	// 5-4, 5-3, 4-3
	data_arr data2;
	data2.push_back(5);
	data2.push_back(4);
	data2.push_back(3);
	run_test(data2, 2, 3);
	
	// Test data 3, expected: 14
	// 5-2, 5-1, 5-4, 5-3
	// 2-1
	// 7-1, 7-6, 7-4, 7-3
	// 6-4, 6-3
	// 8-4, 8-3
	// 4-3
	data_arr data3;
	data3.push_back(5);
	data3.push_back(2);
	data3.push_back(7);
	data3.push_back(1);
	data3.push_back(6);
	data3.push_back(8);
	data3.push_back(4);
	data3.push_back(3);
	run_test(data3, 3, 14);
	
	// Test data 4, expected: 5
	// 6-4, 6-3, 8-4, 8-3, 4-3
	data_arr data4;
	data4.push_back(6);
	data4.push_back(8);
	data4.push_back(4);
	data4.push_back(3);
	run_test(data4, 4, 5);
	
	// Test data 5, expected: 3
	// 6-4, 8-4, 8-7
	data_arr data5;
	data5.push_back(6);
	data5.push_back(8);
	data5.push_back(4);
	data5.push_back(7);
	run_test(data5, 5, 3);
	
	// Test data 6, expected: 57
	// 6-4, 6-1, 6-5, 6-3, 6-2 (5)
	// 8-4, 8-7, 8-1, 8-5, 8-3, 8-2 (6)
	// 4-1, 4-3, 4-2 (3)
	// 7-5, 7-1, 7-3, 7-2 (4)
	// 16-9, 16-14, 16-1, 16-15, 16-11, 16-13, 16-5, 16-12, 16-3, 16-2 (10)
	// 9-1, 9-5, 9-3, 9-2 (4)
	// 14-1, 14-11, 14-13, 14-5, 14-12, 14-3, 14-2 (7)
	// 15-11, 15-13, 15-5, 15-12, 15-3, 15-2 (6)
	// 11-5, 11-3, 11-2 (3)
	// 13-5, 13-12, 13-3, 13-2 (4)
	// 5-3, 5-2 (2)
	// 12-3, 12-2 (2)
	// 3-2 (1)
	// 5+6+3+4+10+4+7+6+3+4+2+2+1 = 57
	data_arr data6;
	data6.push_back(6);
	data6.push_back(8);
	data6.push_back(4);
	data6.push_back(7);
	data6.push_back(16);
	data6.push_back(9);
	data6.push_back(14);
	data6.push_back(1);
	data6.push_back(15);
	data6.push_back(11);
	data6.push_back(13);
	data6.push_back(5);
	data6.push_back(12);
	data6.push_back(3);
	data6.push_back(2);
	run_test(data6, 6, 57);
	
	// Real data
	data_arr data_real;
	ifstream f("IntegerArray.txt");
	val_t in_data;
	while (f >> in_data)
		data_real.push_back(in_data);
	run_test(data_real, 7, 2407905288);
	
	return 0;
}
