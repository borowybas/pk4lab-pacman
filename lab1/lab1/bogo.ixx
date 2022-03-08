export module sorters:bogo;

import <iostream>;
import <vector>;

using namespace std;

// src: https://0x00sec.org/t/sorting-part-4-0-bogo-sort/200
// bogosort
export void bogosort(vector<int>& vec) {
	while (!is_sorted(vec)) shuffle(vec);
}