export module helper;

import <iostream>;
import <vector>;

using namespace std;

// src: https://slaystudy.com/c-merge-sort-vector/
//funkcja pomocnicza merge sort
export void MergeSortedIntervals(vector<int>& v, int s, int m, int e) {
	vector<int> temp;

	int i, j;
	i = s;
	j = m + 1;

	while (i <= m && j <= e) {

		if (v[i] <= v[j]) {
			temp.push_back(v[i]);
			++i;
		}
		else {
			temp.push_back(v[j]);
			++j;
		}

	}

	while (i <= m) {
		temp.push_back(v[i]);
		++i;
	}

	while (j <= e) {
		temp.push_back(v[j]);
		++j;
	}

	for (int i = s; i <= e; ++i)
		v[i] = temp[i - s];

}


// funkcja pomocnicza bogosort
export bool is_sorted(const vector<int>& vec) {

	for (int i = 1, n = vec.size(); i < n; i++) {
		if (vec[i - 1] > vec[i]) return false;
		// returns false if an element is smaller than one to its left
	}

	return true;
}

// funkcja pomocnicza bogosort
export void shuffle(vector<int>& vec) {
	int i, n, tmp, rand_idx;

	for (i = 0, n = vec.size(); i < n; i++) {

		tmp = vec[i]; // store temporarily

		rand_idx = rand() % n; // pick a random index in the vector/array

		// swap each element in vector/array with another one that is chosen randomly
		vec[i] = vec[rand_idx];
		vec[rand_idx] = tmp;
	}
}