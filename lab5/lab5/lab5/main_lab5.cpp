#include <iostream>     
#include <utility>      
#include <future>       
#include <thread> 
#include <Windows.h>
#include <string>

int add_all(std::vector<int> num);
int add(int x, int y);
void printA(int x);
void printB(int x);
void printC(int x);

void avg(std::vector<double> o, std::vector<double> w, std::promise<double> prom);

int main()
{
	int x = 10;
	int y = 5;
	auto sub = [](int x, int y) {return x - y; };
	/*
	Zad_1
	a) Przy pomocy funkcji add dodaj do siebie wszystkie elementy vectora num. Użyj async.
	b)Używając async wywołaj funkcje printA, printB, printC w taki sposób aby stworzyły następujące ciągi: AABCCC,BBBBAC,CBBBBAA.
	Spróbuj osiągnać jak najniższy czas wykonania.
	Wywołania funkcji print stwórz w kolejności alfabetycznej.
	*/
	std::cout << "Zad.1\n";

	std::cout << "a) ";

	std::vector<int> num = { 10, 13, 6, 7, 4, 5 };

	std::future<int> fu = std::async(std::launch::async, add_all, num);
	std::cout << fu.get() << "\n\n";

	std::cout << "b)\n";
	std::cout << "AABCCC\n";

	auto start = std::chrono::high_resolution_clock::now();

	//Tu wpisz rozwiazanie 
	std::async(std::launch::async, printA, 2);
	std::async(std::launch::async, printB, 1);
	std::async(std::launch::async, printC, 3);



	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;//2.2s
	std::cout << std::endl << elapsed << std::endl;

	std::cout << "\nBBBBAC\n";
	/*	//v_1
	std::future<void>  f1 = std::async(std::launch::deferred, printA, 1);
	std::future<void>  f2 = std::async(std::launch::deferred, printB, 4);
	std::future<void>  f3 = std::async(std::launch::deferred, printC, 1);

	f2.get();
	f1.get();
	f3.get();*/
	start = std::chrono::high_resolution_clock::now();

	//Tu wpisz rozwiazanie v_2
	std::future<void>  f1 = std::async(std::launch::async, printA, 1);
	std::future<void>  f2 = std::async(std::launch::async, printB, 4);
	Sleep(550);
	std::future<void>  f3 = std::async(std::launch::async, printC, 1);

	f2.get();
	f1.get();
	f3.get();

	end = std::chrono::high_resolution_clock::now();
	elapsed = end - start;
	std::cout << std::endl << elapsed << std::endl;//1.5s

	std::cout << "\nCBBBBAA\n";

	start = std::chrono::high_resolution_clock::now();

	//Tu wpisz rozwiazanie

	std::future<void>  fu1 = std::async(std::launch::deferred, printA, 2);
	std::future<void>  fu2 = std::async(std::launch::deferred, printB, 4);
	std::future<void>  fu3 = std::async(std::launch::deferred, printC, 1);
	
	fu3.get();
	fu2.get();
	fu1.get();

	end = std::chrono::high_resolution_clock::now();
	elapsed = end - start;
	std::cout << std::endl << elapsed << std::endl;//1s


	/*
	Zad_2
	a)Tworząc tylko po jednym packaged_task dla add i sub oblicz wartość: add(x,sub(y,x)).
	b)Tworząc tylko po jednym packaged_task dla każdej funkcji print, wyswietl następujace ciągi: AACBA,BBCCAABC,CBABC. (dla 1 ciagu) lacznie 9
	*/
	std::cout << "\nZad_2\n";
	std::cout << "a) ";

	//Tu wpisz rozwiazanie
	std::packaged_task<int(int, int)> pt_add(add);
	std::packaged_task<int(int, int)> pt_sub(sub);
	std::future<int> futu = pt_add.get_future();
	std::future<int> futu1 = pt_sub.get_future();
	pt_sub(y, x);
	pt_add(x, futu1.get());

	std::cout << futu.get() << "\n";

	std::cout << "\nb)\n";
	std::cout << "AACBA\n";

	//Tu wpisz rozwiazanie
	std::packaged_task<void(int)> pt_A(printA);
	std::packaged_task<void(int)> pt_B(printB);
	std::packaged_task<void(int)> pt_C(printC);

	std::future<void> futur1 = pt_A.get_future();
	std::future<void> futur2 = pt_B.get_future();
	std::future<void> futur3 = pt_C.get_future();

	pt_A(2);
	pt_A.reset();
	futur1 = pt_A.get_future();
	pt_C(1);
	pt_B(1);
	pt_A(1);

	std::cout << "\nBBCCAABC\n";

	//Tu wpisz rozwiazanie
	std::packaged_task<void(int)> ptask_A(printA);
	std::packaged_task<void(int)> ptask_B(printB);
	std::packaged_task<void(int)> ptask_C(printC);

	std::future<void> f_A = ptask_A.get_future();
	std::future<void> f_B = ptask_B.get_future();
	std::future<void> f_C = ptask_C.get_future();

	ptask_B(2);
	ptask_B.reset();
	f_B = ptask_B.get_future();
	ptask_C(2);
	ptask_C.reset();
	f_B = ptask_C.get_future();
	ptask_A(2);
	ptask_B(1);
	ptask_C(1);

	std::cout << "\nCBABC\n";

	//Tu wpisz rozwiaznie
	std::packaged_task<void(int)> pac_task_A(printA);
	std::packaged_task<void(int)> pac_task_B(printB);
	std::packaged_task<void(int)> pac_task_C(printC);

	std::future<void> fu_A = pac_task_A.get_future();
	std::future<void> fu_B = pac_task_B.get_future();
	std::future<void> fu_C = pac_task_C.get_future();

	pac_task_C(1);
	pac_task_C.reset();
	fu_C = pac_task_C.get_future();
	pac_task_B(1);
	pac_task_B.reset();
	fu_B = pac_task_B.get_future();
	pac_task_A(1);
	pac_task_B(1);
	pac_task_C(1);

	/*
	Zad_3
	Stwórz funkcję typu void, wypisującą średnią ważoną ocen.
	Funkcja powinna wykonywać się na osobnym wątku.
	Skorzystaj z promise.
	*/

	std::cout << "\n\nZad_3\n";
	std::vector<double>oceny = { 2, 5, 3, 3, 4, 5, 2 };
	std::vector<double>wagi = { 4, 2, 3, 4, 4, 3, 2 };

	std::promise<double> prom;
	std::future<double> fu_last = prom.get_future();
	std::thread th(avg, oceny, wagi, std::move(prom));
	std::cout << fu_last.get()<< "\n";
	th.join();
}

void avg(std::vector<double> o, std::vector<double> w, std::promise<double> prom){
	double numerator = 0;
	double denominator = 0;
	
	for (auto i = 0; i < o.size(); i++) {
		numerator += o[i] * w[i];
		denominator += w[i];
	}
	double result = numerator/denominator;
	prom.set_value(result);
}

int add_all(std::vector<int> num) {
	int res = 0;
	for (int i : num)
		res += i;
	return res;
}

int add(int x, int y)
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