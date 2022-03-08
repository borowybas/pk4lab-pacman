export module sorters:merge;

import <iostream>;
import <vector>;

using namespace std;

// merge sort
export void MergeSort(vector<int>& v, int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		MergeSort(v, s, m);
		MergeSort(v, m + 1, e);
		MergeSortedIntervals(v, s, m, e);
	}
}