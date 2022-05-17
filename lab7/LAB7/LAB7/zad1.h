const std::chrono::milliseconds SLEEP(10);
const int LOOP = 3;
//Tu zadeklaruj semafory
std::counting_semaphore sem_a(0);
std::counting_semaphore sem_b(0);
std::counting_semaphore sem_c(0);


//Funkcje do zad1a - w nich dokonujesz zmian
void aprintA()
{
    for (int i = 0; i < 3 * LOOP; i++)
    {
        sem_a.acquire();
        std::cout << "A";
        sem_c.release();
    }
}

void aprintB()
{
    for (int i = 0; i < 2 * LOOP; i++)
    {
        sem_b.acquire();
        std::cout << "B";
        sem_c.release();
    }
}

void aprintC()
{
    for (int i = 0; i < 1 * LOOP; i++)
    {
        sem_a.release();
        sem_a.release();
        sem_a.release();

        sem_c.acquire();
        sem_c.acquire();
        sem_c.acquire();

        sem_b.release();
        sem_b.release();

        sem_c.acquire();
        sem_c.acquire();

        std::cout << "C";
    }
}
//BABBCC
//Funkcje do zad1b - w nich dokonujesz zmian 
void bprintA()
{
    for (int i = 0; i < 1 * LOOP; i++)
    {
        sem_b.release();
        sem_a.acquire();

        std::cout << "A";

        sem_b.release();
        sem_a.acquire();

        sem_b.release();
        sem_a.acquire();

        sem_c.release();
        sem_a.acquire();

        sem_c.release();
        sem_a.acquire();
    }
}

void bprintB()
{
    for (int i = 0; i < 3 * LOOP; i++)
    {
        sem_b.acquire();
        std::cout << "B";
        sem_a.release();
    }
}

void bprintC()
{
    for (int i = 0; i < 2 * LOOP; i++)
    {
        sem_c.acquire();
        std::cout << "C";
        sem_a.release();
    }
}
//CABCCA
//Funkcje do zad1c - w nich dokonujesz zmian 
void cprintA()
{
    for (int i = 0; i < 2 * LOOP; i++)
    {
        sem_a.acquire();
        std::cout << "A";
        sem_b.release();
    }
}

void cprintB()
{
    for (int i = 0; i < 1 * LOOP; i++)
    {
        sem_c.release();
        sem_b.acquire();

        sem_a.release();
        sem_b.acquire();

        std::cout << "B";

        sem_c.release();
        sem_b.acquire();

        sem_c.release();
        sem_b.acquire();

        sem_a.release();
        sem_b.acquire();
    }
}

void cprintC()
{
    for (int i = 0; i < 3 * LOOP; i++)
    {
        sem_c.acquire();
        std::cout << "C";
        sem_b.release();
    }
}


//Poni¿szych funkcji nie modyfikuj :)
void zad1a()
{
    std::cout << "Zadanie 1a) AAABBC\n";
    std::thread threadA(aprintA);
    std::thread threadB(aprintB);
    std::thread threadC(aprintC);
    threadA.join();
    threadB.join();
    threadC.join();
}
void zad1b()
{
    std::cout << "\nZadanie 1b) BABBCC\n";
    std::thread threadA(bprintA);
    std::thread threadB(bprintB);
    std::thread threadC(bprintC);
    threadA.join();
    threadB.join();
    threadC.join();
}
void zad1c()
{
    std::cout << "\nZadanie 1c) CABCCA\n";
    std::thread threadA(cprintA);
    std::thread threadB(cprintB);
    std::thread threadC(cprintC);
    threadA.join();
    threadB.join();
    threadC.join();
}