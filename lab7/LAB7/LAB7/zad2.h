#pragma once
constexpr int PLAYERS = 8;          //liczba graczy/w¹tków
constexpr int ROUNDS = 3;           //liczba rund

int results[PLAYERS] = { 0 };       //tu przechowywane s¹ wyniki rzutu kostk¹ (liczby 1-6)
bool status[PLAYERS] = { 0 };       //tu przechowywana jest informacja o zwyciêstwie/przegranej danego gracza
std::atomic_bool GameActive = true; //informuje, ¿e gra jest w toku

//Tu zadeklaruj bariery
std::barrier bariera_1(PLAYERS + 1);
std::barrier bariera_2(PLAYERS + 1);

void roll(int Index)
{
    srand(Index);
    while (GameActive)
    {
        results[Index] = rand() % 6 + 1;    //rzut kostk¹
        bariera_1.arrive_and_wait();
        bariera_2.arrive_and_wait();
        if (status[Index] == 1) printf("Gracz nr %d. wyrzucil %2d - WYGRANA!\n", Index + 1, results[Index]);
        else printf("Gracz nr %d. wyrzucil %2d - przegrana.\n", Index + 1, results[Index]);
    }
}

void zad2()
{
    std::cout << "Zadanie 2.\n";
    std::vector<std::thread> Threads;               //deklaracja w¹tków
    for (int i = 0; i < PLAYERS; i++)
        Threads.push_back(std::thread(roll, i));    //uruchomienie rzutu monet¹

    for (int r = 0; r < ROUNDS; ++r)
    {
        bariera_1.arrive_and_wait();
        std::cout << "==== Runda nr " << r + 1 << ". ====\n";
        int max = 0;
        for (int i = 0; i < Threads.size(); i++) //szukanie najwy¿szego wyniku
        {
            if (results[i] > max) max = results[i];
        }

        for (int i = 0; i < Threads.size(); i++) //sprawdzenie, czy dany gracz osi¹gn¹³ najwy¿szy wynik
        {
            if (results[i] == max) status[i] = 1;
            else status[i] = 0;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        bariera_2.arrive_and_wait();
    }

    GameActive = false;
    for (size_t i = 0; i < Threads.size(); i++) Threads[i].join();
}