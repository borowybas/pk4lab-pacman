#pragma once
const int COUNT = 1000000;						//liczba iteracji
std::atomic_bool blad=0;						//czy na jakimkolwiek etapie pojawi³ siê b³¹d?
int liczba_produktow_A = 0;
int liczba_produktow_B = 0;

//Tu zadeklaruj semafory
std::counting_semaphore bufor(1);
std::counting_semaphore miejsce(100);
std::counting_semaphore dane_a(0);
std::counting_semaphore dane_b(0);


void ProducentA()
{
	for (int i = 0; i < COUNT; i++)
	{
		miejsce.acquire();

		bufor.acquire();
		++liczba_produktow_A;	//proces produkcji
		bufor.release();

		dane_a.release();

		if (liczba_produktow_A < 0 || liczba_produktow_B < 0) blad = 1;
	}
}

void ProducentB()
{
	for (int i = 0; i < COUNT; i++)
	{
		miejsce.acquire();

		bufor.acquire();
		++liczba_produktow_B;	//proces produkcji
		bufor.release();

		dane_b.release();

		if (liczba_produktow_A < 0 || liczba_produktow_B < 0) blad = 1;
	}
}

void KonsumentA()
{
	for (int i = 0; i < COUNT; i++)
	{
		dane_a.acquire();

		bufor.acquire();
		--liczba_produktow_A;	//proces konsumpcji
		bufor.release();

		miejsce.release();

		if (liczba_produktow_A < 0 || liczba_produktow_B < 0) blad = 1;
	}
}

void KonsumentB()
{
	for (int i = 0; i < COUNT; i++)
	{
		dane_b.acquire();

		bufor.acquire();
		--liczba_produktow_B;	//proces konsumpcji
		bufor.release();

		miejsce.release();

		if (liczba_produktow_A < 0 || liczba_produktow_B < 0) blad = 1;
	}
}

void zad3()
{
	std::cout << "Zadanie 3.\n";
	std::thread PA(ProducentA);
	std::thread PB(ProducentB);
	std::thread KA(KonsumentA);
	std::thread KB(KonsumentB);
	PA.join();
	PB.join();
	KA.join();
	KB.join();
	if (blad) std::cout << "Cos poszlo nie tak - liczba elementow spadla ponizej zera!\n";
	else std::cout << "Wszystko przebieglo pomyslnie!\n";
}