#include <iostream>
#include <thread>
#include <barrier>
#include <semaphore>
#include "zad1.h"
#include "zad2.h"
#include "zad3.h"

//UWAGA! Upewnij się, że korzystasz ze standardu C++20!

int main()
{
    //Zadanie 1 - zedytuj ciała funkcji aprintA(), aprintB(), aprintC(), bprintA()...
    //w pliku "zad1.h" i odkomentuj potrzebne wywołania poniżej:
    zad1a();
    zad1b();
    zad1c();
    
    std::cout << "\n------------------\n";
    //Zadanie 2 - w pliku zad2.h dodaj dwie bariery oraz zedytuj ciała funkcji roll() i zad2().
    zad2();

    std::cout << "\n------------------\n";
    //Zadanie 3 - w pliku zad3.h dodaj cztery semafory i zarządzaj nimi w procesach konsumentów i producentów.
    zad3();
    return 0;
}
