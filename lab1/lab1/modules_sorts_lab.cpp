import sorters;

import <iostream>;
import <vector>;

using namespace std;



int main() {
	// pocz�tek wpisywania testowego vectora
	int n;
	std::vector<int> v;

	cout << "Podaj rozmiar vectora: ";
	cin >> n;
	v = vector<int>(n);
	cout << "Podaj elementy: ";
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
	}
	// koniec wpisywania testowego vectora

	// wywo�ania funkcji sortuj�cych
	bubbleSort(v);
	//MergeSort(v, 0, n - 1);
	//bogosort(v);


	// prezentacja wynik�w sortowania
	cout << "\nWynik sortowania: ";
	for (int i = 0; i < n; ++i) {
		cout << v[i] << ' ';
	}
}