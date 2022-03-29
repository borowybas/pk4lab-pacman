#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <numeric>

bool isPrime(int i)
{
	for (int j = 2; j * j <= i; ++j) {
		if (i % j == 0) return false;
	}
	return true;
}

int main()
{

	//Przydatne linki
	//	https://en.cppreference.com/w/cpp/ranges
	//	https://en.cppreference.com/w/cpp/algorithm/ranges
	//	https://en.cppreference.com/w/cpp/ranges/iota_view
	//	https://hannes.hauswedell.net/post/2019/11/30/range_intro/
	//	https://www.modernescpp.com/index.php/c-20-functional-patterns-with-the-ranges-library
	//	https://itnext.io/c-20-ranges-complete-guide-4d26e3511db0

	/*Zadanie 1 : Utwórz nowy vector do którego u¿ywajac biblioteki ranges wpiszesz podwojone
				  liczby podzielne przez 3 znajdujace sie w vector numbers
	*/

	std::cout << "zadanie 1 " << std::endl;
	std::vector<int> numbers = { 6,2,8,9,10,12,8,1,16,8,15,21,8,3,18,23,27,45,8,37,2 };
	//Rozwiazanie
	std::vector<int> vec;

	auto div3 = [](int a) {return a % 3 == 0; };
	namespace rv = std::ranges::views;

	for (int i : rv::reverse(numbers) | rv::filter(div3) | rv::take(numbers.size()) | rv::reverse) {
		std::cout << i << " ";
		vec.push_back(2*i);
	}
	std::cout << std::endl;

	/*Zadanie 2 : U¿ywajac biblioteki ranges
					a. znajdŸ i wyswietl na ekranie Najwiêkszy i najmniejszy element vectora numbers.
					b. Wypisuj elementy wektora numbers1 tak d³ugo, jak s¹ to potêgi dwójki.
					   Nastêpnie policz iloœæ wszystkich wyst¹pieñ potêg dwójki w wektorze
					c. posortuj vector numbers od 10 elementu do konca
					d. pomieszaj vector vec0, a nastepnie pomno¿ ka¿dy element razy 2
	*/
	std::cout << "zadanie 2 " << std::endl;
	//Rozwiazanie
	//a
	std::cout << "a" << std::endl;

	auto max_el = std::ranges::max_element(numbers);
	std::cout << "max el: " << numbers[std::ranges::distance(numbers.begin(), max_el)]<<std::endl;

	auto min_el = std::ranges::min_element(numbers);
	std::cout << "min el: " << numbers[std::ranges::distance(numbers.begin(), min_el)] << std::endl;;


	//b
	std::cout << "b " << std::endl;

	std::vector<int> numbers1{ 2,4,8,16,32,64,70,128 };

	auto powerOf2 = [](int n) {return (n & (n - 1)) == 0; };
	namespace rv = std::ranges::views;
	int num = 0;

	for (int i : std::ranges::take_while_view(numbers1, powerOf2)) {
		std::cout << i << " ";
		num++;
	}

	std::cout << std::endl<<"ilosc wystapien potegi 2: "<<num<<std::endl;

	//c
	std::cout << "c" << std::endl;

	std::ranges::sort(std::ranges::drop_view{numbers, 10});
	for (int i = 0; i < numbers.size(); i++) {
		std::cout << numbers[i] << " ";
	}

	//d 
	std::cout << "\n\n";
	std::cout << "d" << std::endl;
	std::vector<int> vec0{ 1,43,432,6,876,23,5 };
	
	std::random_device rd;
	std::mt19937 gen{ rd() };
	std::ranges::shuffle(vec0,gen);

	for (int i = 0; i < vec0.size(); i++) {
		std::cout << vec0[i] << " ";
	}


	/*Zadanie 3: U¿ywajac biblioteki ranges
	*				a. po³¹cz ze sob¹ vec1 i vec2 (stwórz nowy wektor bêd¹cy ich po³¹czeniem (posortowany)
	*				b. po³acz ze soba vec1 i vec2 bez powtarzania elementów (zapisz wynik do nowego wektora)
	*				c. znajdz roznicê (w sensie wynik odejmowania na zbiorach) vec1 - vec2 (ró¿nicê zapisz do nowego wektora)
	*/
	std::cout << std::endl;
	std::cout << "zadanie 3 " << std::endl;


	std::vector<int> vec1 = { 1,2,3,4,5,6 };
	std::vector<int> vec2 = { 5,6,7,8,9 };

	//a
	std::cout << "a" << std::endl;
	std::vector<int> nowya, nowyb, nowyc;

	std::ranges::merge(vec1, vec2, std::back_inserter(nowya));
	for (int i = 0; i < nowya.size(); i++) {
		std::cout << nowya[i] << " ";
	}
	std::cout << std::endl;


	//b
	std::cout << "b" << std::endl;

	std::ranges::set_union(vec1, vec2, std::back_inserter(nowyb));
	for (int i = 0; i < nowyb.size(); i++) {
		std::cout << nowyb[i] << " ";
	}
	std::cout << std::endl;

	//c
	std::cout << "c" << std::endl;

	std::ranges::set_difference(vec1, vec2, std::back_inserter(nowyc));
	for (int i = 0; i < nowyc.size(); i++) {
		std::cout << nowyc[i] << " ";
	}
	std::cout << std::endl;

	//Zadanie 4: U¿ywajac biblioteki ranges - wypisz 20 liczb pierwszych pocz¹wszy od 100000.

	std::cout << "\nzadanie 4\n";

	auto prime = [](int a) { 
		for (int i = 2; i <= a / 2; ++i) {
			if (a % i == 0) {
				return false;
			}
		}
		return true;
	};

	int twenty = 20;
	
	for (int i : std::views::iota(100000)  | std::ranges::views::filter(prime)) {
		std::cout << i << std::endl;
		twenty--;
		if (twenty <= 0) break;
	}
}