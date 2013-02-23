#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * Value printer
 */
void value_printer(int val)
{
	cout << val << ", ";
}

/**
 * MergeSort merge function
 */
vector<int> merge_func(vector<int> data, vector<int> data2)
{
	vector<int>::iterator it1 = data.begin();
	vector<int>::iterator it2 = data2.begin();
	vector<int> result;
	
	while (it1 != data.end() && it2 != data2.end())
	{
		if (*it1 < *it2) {
			result.push_back(*it1);
			it1++;
		}
		else {
			result.push_back(*it2);
			it2++;
		}
	}
	
	if (it1 != data.end()) {
		result.insert(result.end(), it1, data.end());
	}
	else if (it2 != data2.end()) {
		result.insert(result.end(), it2, data2.end());
	}
	
	return result;
}

/**
 * Sort function impl
 */
vector<int> merge_sort_func(vector<int> data)
{
	if (data.size() > 1) {
		int midIndex = data.size()/2;
		vector<int> left(midIndex);
		vector<int> right(data.size()-midIndex);
		
		copy(data.begin(), data.begin()+midIndex, left.begin());
		copy(data.begin()+midIndex, data.end(), right.begin());
		
		return merge_func(
					merge_sort_func(left),
					merge_sort_func(right)
		);
	}
	
	return data;
}

/**
 * Run test for specified vector
 */
void run_test(vector<int> &v, int testNum)
{
	// Initial
	cout << endl << "Running test#" << testNum << "..." << endl;
	cout << "Initial: ";
	for_each(v.begin(), v.end(), value_printer);
	cout << endl;
	
	// Merge Sort
	vector<int> result = merge_sort_func(v);
	
	// Results
	cout << "Result: ";
	for_each(result.begin(), result.end(), value_printer);
	cout << endl;
}


/**
 * MergeSort test
 */
int main()
{
	vector<int> data;
	data.push_back(5);
	data.push_back(2);
	data.push_back(7);
	data.push_back(1);
	data.push_back(6);
	data.push_back(8);
	data.push_back(4);
	data.push_back(3);
	run_test(data, 1);
	
	vector<int> data2;
	data2.push_back(5);
	run_test(data2, 2);
	
	vector<int> data3;
	data3.push_back(5);
	data3.push_back(2);
	run_test(data3, 3);
	
	vector<int> data4;
	data4.push_back(5);
	data4.push_back(2);
	data4.push_back(1);
	data4.push_back(1);
	data4.push_back(2);
	run_test(data4, 4);
	
	vector<int> data5;
	data5.push_back(2);
	data5.push_back(5);
	run_test(data5, 5);	
	
	return 0;
}
