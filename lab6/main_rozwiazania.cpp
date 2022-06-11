#include <iostream>     
#include <utility>      
#include <future>       
#include <thread> 
#include <Windows.h>

int add_all(std::vector<int> num) {
	int res = 0;
	for (int i : num)
		res += i;
	return res;
}

int add(int x,int y)
{ 
	return x + y;
}

void printA(int x) {

	Sleep(1000);
	for (int i = 0; i < x; i++) {
		std::cout << "A";
	}
}

void printB(int x) {

	Sleep(750);
	for (int i = 0; i < x; i++) {
		std::cout << "B";
	}
}

void printC(int x) {

	Sleep(500);
	for (int i = 0; i < x; i++) {
		std::cout << "C";
	}
}

void SredWa(std::vector<double>oceny, std::vector<double> wagi,std::promise<double> prom) {

	double licznik = 0, mianownik = 0;
	for (int i = 0; i < oceny.size(); i++) {
		licznik += oceny.at(i) * wagi.at(i);
		mianownik += wagi.at(i);
	}

	prom.set_value(licznik / mianownik);

}

int main()
{
	int x = 10;
	int y = 5;
	auto sub = [](int x, int y) {return x - y; };
	/*
	Zad_1
	a)U¿ywaj¹c async dla add dodaj dodaj do siebie wszystkie elementy z num;

	b)U¿ywaj¹c async wywo³aj funkcjiê printA, printB, printC w taki sposób ¿e sworz¹ nastêpuj¹ce ci¹gi AABCCC,BBBBAC,CBBBBAA spubój osi¹gn¹æ taki sam lub leprzy czas jak ja.
	Wywo³ania twórz w kolejnoœci alfabetycznej.
	*/
	std::cout << "Zad.1\n";

	std::cout << "a)\n";

	std::vector<int> num = { 10, 13, 6, 7, 4, 5 };
	int res = 0;
	for (int i : num) {
		std::future<int> fu = std::async(std::launch::async, add, res, i);
		res = fu.get();
	}
	std::cout << "result\n";
	std::cout << res;
	;


	std::cout << "b)\n";
	std::cout << "AABCCC\n";

	auto start = std::chrono::high_resolution_clock::now();

	std::future<void> fu1 = std::async(std::launch::async, printA, 2);
	std::future<void> fu2 = std::async(std::launch::deferred, printB, 1);
	std::future<void> fu3 = std::async(std::launch::deferred, printC, 3);
	fu1.wait();
	fu2.get();
	fu3.get();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;//2.2s
	std::cout << std::endl << elapsed<<std::endl;

	std::cout << "\nBBBBAC\n";

	start = std::chrono::high_resolution_clock::now();
	std::chrono::microseconds span(1200);
	fu1 = std::async(std::launch::async, printA, 1);
	fu2 = std::async(std::launch::async, printB, 4);
	fu3 = std::async(std::launch::deferred, printC, 1);
	fu1.wait();
	fu3.get();


	end = std::chrono::high_resolution_clock::now();
	elapsed = end - start;
	std::cout << std::endl << elapsed << std::endl;//1.5s

	std::cout << "\nCBBBBAA\n";

	start = std::chrono::high_resolution_clock::now();

	fu1 = std::async(std::launch::async, printA, 2);
	fu2 = std::async(std::launch::async, printB, 4);
	fu3 = std::async(std::launch::async, printC, 1);

	fu1.wait();
	end = std::chrono::high_resolution_clock::now();
	elapsed = end - start;
	std::cout << std::endl << elapsed << std::endl;//1s
	

	/*
	Zad_2
	a)Tworz¹c tylko po jednym packaged_task dla add i sub oblicz wartoœci add(x,sub(y,x)).

	b)Tworz¹c tylko po jednym packaged_task dla ka¿dych funkcji print dla ka¿dego ci¹gu wyœwitl nastêpuj¹ce ci¹gi AACBA,BBCCAABC,CBABC.
	*/
	std::cout << "\nZad_2\n";
	std::cout << "\na)\n";
	std::packaged_task<int(int, int)> addPT(add);
	std::future<int> addF = addPT.get_future();
	std::packaged_task<int(int, int)> subPT(sub);
	std::future<int> subF = subPT.get_future();
	subPT(x, y);
	int sub1 = subF.get();
	addPT(x, sub1);
	int res2 = addF.get();
	std::cout << "Res = " << res2;

	std::cout << "\nb)\n";
	std::cout<<"AACBA\n";

	std::packaged_task<void(int)> PrintA1(printA);
	std::future<void> fA1 = PrintA1.get_future();
	PrintA1(2);
	
	std::packaged_task<void(int)> PrintC1(printC);
	std::future<void> fC1 = PrintC1.get_future();
	PrintC1(1);

	std::packaged_task<void(int)> PrintB1(printB);
	std::future<void> fB1 = PrintB1.get_future();
	PrintB1(1);

	PrintA1.reset();
	fA1 = PrintA1.get_future();
	std::thread th(std::move(PrintA1), 1);

	th.join();
	std::cout << "\nBBCCAABC\n";

	std::cout << "\CBABC\n";
	/*
	Zad_3
	Stwórz funkciê zwracaj¹c¹ void obliczaj¹ca œredni¹ wa¿on¹ vactorów par gdzie pierszy element pary to wartoœæ a drugi to jej waga. Funkcja powinna wykonywaæ siê na osobnym w¹tku.
	Skorzystaj z promise.
	*/
	std::cout << "Zad_3\n";
	std::vector<double>oceny = { 2, 5, 3, 3, 4, 5, 2 };
	std::vector<double>wagi = { 4, 2, 3, 4, 4, 3, 2 };
	std::promise<double> prom;
	std::future<double> promf = prom.get_future();
	std::thread Promth(SredWa,oceny,wagi,std::move(prom));
	std::cout << promf.get();
	Promth.join();
	
}

