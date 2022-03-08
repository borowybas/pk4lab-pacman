export module sorters:bubble;

import <iostream>;
import <vector>;

using namespace std;

// src: https://stackoverflow.com/questions/30963204/c-vector-bubble-sort
// bubble sort
 export void bubbleSort(vector<int>& a)
{
	bool swapp = true;
	while (swapp) {
		swapp = false;
		for (size_t i = 0; i < a.size() - 1; i++) {
			if (a[i] > a[i + 1]) {
				a[i] += a[i + 1];
				a[i + 1] = a[i] - a[i + 1];
				a[i] -= a[i + 1];
				swapp = true;
			}
		}
	}
}