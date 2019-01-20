#include <fstream>
#include <iostream>
#include <conio.h>
#include <cmath>
#include <queue>
#include <vector>
#include <ctime>


int cityamount = 0;
int **distances;
bool divers = true;


void chosingfile();
bool fileread(std::string);
void writetab(int**);
void menu();
int genetical(int, int, int, int, char, char, int, int);


int  main()
{
    srand(time(NULL));
    chosingfile();
    menu();

//    getche();
}


void chosingfile()
{
    std::string filename = "ftv47.atsp";
    int choice = 0;
    while(choice != '1' && choice != '2'){
        std::cout << " Wybierz plik do wczytania: ";
        std::cout << "\n 1.Wpisz nazwe pliku do wczytania";
        std::cout << "\n 2.Wczytaj domyslny plik tekstowy \"ftv47.atsp\"";
        std::cout << "\nTwoj wybor: ";
        choice = getche(); // pobieranie jednego znaku z klawiatury w formie kodu ascii
        switch (choice){
            case '1':
                std::cout << "\nPodaj nazwe pliku: ";
                std::cin >> filename;
//                if(fileread(filename) == 0){
//                    std::cout << "Nie udalo sie wczytac pliku o podanej nazwie, sprobuj ponownie! \n";
//                    choice = 0;
//                }
//                break;
            case '2':
                if(fileread(filename) == 0){
                    std::cout << "\nNie udalo sie wczytac pliku, sproboj ponownie! \n";
                    choice = 0;
                }
                break;
            default:
                std::cout << "\nWybrano zla liczbe, prosze powtorzyc! \n";
                break;
        }
    }
    std::cout << "\nPlik " << filename << " zostal wczytany poprawnie.";
}


bool fileread(std::string filename)         // funkcja do odczytywania danych z pliku
{
    std::fstream plik;
    plik.open(filename,std::ios::in);
    if(plik.good())                         // sprawdzenie poprawnosci wczytania pliku, w razie niepowodzenia zwracamy blad
    {
        plik>>cityamount;
        distances = new int* [cityamount];   // dwuwymiarowa tablica dynamiczna
        for(int i=0;i<cityamount;++i)
            distances[i]=new int[cityamount];
        for(int i=0;i<cityamount;++i)       // zapelnianie tablicy danymi z pliku
            for(int j=0;j<cityamount;++j)
                plik>>distances[i][j];
        return 1;
    }
    return 0;
}


void writetab(int** cities)
{
    std::cout << "\n\n";
    std::cout << cityamount << '\n';
    for(int i=0;i<cityamount;++i)
    {
        for(int j=0;j<cityamount;++j)
            std::cout<<cities[i][j]<<" ";
        std::cout<<"\n";
    }
}


void menu()
{
    int kstropu = '1';
    int maxiteracja = 1000;
    int ttime = 4;
    int wlkpopulacji = 50;
    char mkrzyzowania = '1';
    char mmutacji = '1';
    int wspkrzyzowania = 80;
    int wspmutacji = 1;

    int choice = -1;
    while(choice != '0')
    {
        std::cout << "\n\n\n Aktualnie ustawione parametry programu: ";
        if(kstropu == '1' || kstropu == '3') std::cout << "\n Czas jednego wykonania algorytmu (w sekundach): " << ttime;
        if(kstropu == '3') std::cout << " lub gdy sie wykona";
        if(kstropu == '2' || kstropu == '3') std::cout << "\n maskymalna ustawiona liczba iteracji: " << maxiteracja;
        if(mkrzyzowania == '1') std::cout << "\n Metoda krzyzowania: OX";
        if(mkrzyzowania == '2') std::cout << "\n Metoda krzyzowania: PMX";
        std::cout << "\n Wspolczynnik krzyzowania: " << wspkrzyzowania;
        if(mmutacji == '1') std::cout << "\n Metoda mutacji: insert";
        if(mmutacji == '2') std::cout << "\n Metoda mutacji: invert";
        if(mmutacji == '3') std::cout << "\n Metoda mutacji: swap";
        std::cout << "\n Wspolczynnik mutacji: " << wspmutacji;
        std::cout << "\n Wielkosc populacji: " << wlkpopulacji;

        std::cout << "\n\n Wybierz opcje do rozwiazania TSP:";
        std::cout << "\n1. Wybierz nowy plik z danymi";
        std::cout << "\n2. Wyswietl aktualnie wczytany plik";
        std::cout << "\n3: Ustaw Kryterium Stopu";
        std::cout << "\n4: Ustaw Wspolczynnik Krzyzowania";
        std::cout << "\n5: Ustaw Wspolczynnik Mutacji";
        std::cout << "\n6: Ustaw Metode Krzyzowania";
        std::cout << "\n7: Ustaw Metode Mutacji";
        std::cout << "\n8. Ustaw Wielkosc Populacji";
        std::cout << "\n9: Algorytm Genetyczny";
        std::cout << "\n0. Wyjscie ";
        std::cout << "\n\nt. Wielokrotne Testowanie Algorytmu";
        std::cout << "\nTwoj wybor: ";

        choice = getche();
        switch(choice)
        {
        case '1':
        {
            for(int i=0;i<cityamount;++i)        // zwolnij pamiec
                delete[] distances[i];
            delete[] distances;
            std::cout <<"\n\n";
            chosingfile();
            break;
        }
        case '2':
        {
            std::cout << " \nZawarte w nim dane to: \n";
            writetab(distances);
            break;
        }
        case '3':
        {
            do {
                std::cout << "\n\n Wybierz warunek koncowy wykonywania algorytmu: ";
                std::cout << "\n 1. Okreslony czas (w sekundach)";
                std::cout << "\n 2. Okreslona ilosc iteracji";
                std::cout << "\n 3. Oba powyzsze";
                std::cout << "\n Twoj wybor: ";
                kstropu = getche();
                if(kstropu == '1' || kstropu == '3')
                    do
                    {
                        std::cout << "\n\n Podaj czas wykonywania algorytmu (w sekundach): ";
                        std::cin >> ttime;
                        if(ttime <= 0) std::cout << "\n Czas wykonywania musi byc wiekszy od zera! Sprobuj ponownie!";
                    }while(ttime <=0);
                if(kstropu == '2' || kstropu == '3')
                    do
                    {
                        std::cout << "\n\n Podaj maksymalna liczbe iteracji programu: ";
                        std::cin >> maxiteracja;
                        if(maxiteracja <= 0) std::cout << "\n Liczba iteracji musi byc wieksza od zera! Sprobuj ponownie!";
                    }while(maxiteracja <= 0);
                if(kstropu != '1' && kstropu != '2' && kstropu != '3') std::cout << "\n\n Sprobuj jeszcze raz wybrac warunek zakonczenia dzialania algorytmu!";
            } while (kstropu != '1' && kstropu != '2' && kstropu != '3');
            break;
        }
        case '4':
        {
            do {
                std::cout << "\n\n Podaj wartosc wspolczynnika krzyzowania: ";
                std::cin >> wspkrzyzowania;
                if(wspkrzyzowania <= 0) std::cout << "\n Wspolczynnik krzyzowania musi byc wiekszy od zera! Sprobuj ponownie!";
            } while (wspkrzyzowania <=0);
            break;
        }
        case '5':
        {
            do {
                std::cout << "\n\n Podaj wartosc wspolczynnika mutacji: ";
                std::cin >> wspmutacji;
                if(wspmutacji <= 0) std::cout << "\n Wspolczynnik mutacji musi byc wiekszy od zera! Sprobuj ponownie!";
            } while (wspmutacji <=0);
            break;
        }
        case '6':
        {
            do {
                std::cout << "\n\n Wybierz metode krzyzowania z ponizszych: ";
                std::cout << "\n 1. OX";
                std::cout << "\n 2. PMX";
                std::cout << "\n Twoj wybor: ";
                mkrzyzowania = getche();
                if(mkrzyzowania != '1' && mkrzyzowania != '2') std::cout << "\n Nie ma takiej metody! Sprobuj ponownie!";
            } while (mkrzyzowania != '1' && mkrzyzowania != '2');
            break;
        }
        case '7':
        {
            do {
                std::cout << "\n\n Podaj wielkosc populacji (zakres testowy: 10 - 500): ";
                std::cin >> wlkpopulacji;
                if(wlkpopulacji < 10 || wlkpopulacji > 500) std::cout << "\n Wielkosc nie miesci sie w zakresie! Sprobuj ponownie!";
            } while (wlkpopulacji < 10 || wlkpopulacji > 500);
            break;
        }
        case '8':
        {
            do {
                std::cout << "\n\n Wybierz metode mutacji z ponizszych: ";
                std::cout << "\n 1. insert";
                std::cout << "\n 2. invert";
                std::cout << "\n 3. swap";
                std::cout << "\n Twoj wybor: ";
                mmutacji = getche();
                if(mmutacji != '1' && mmutacji != '2' && mmutacji != '3') std::cout << "\n Nie ma takiej metody! Sprobuj ponownie!";
            } while (mmutacji != '1' && mmutacji != '2' && mmutacji != '3');
            break;
        }
        case '9':
        {

            std::cout << "\n\n " << genetical(kstropu, maxiteracja, ttime, wlkpopulacji, mkrzyzowania, mmutacji, wspkrzyzowania, wspmutacji);
            break;
        }
        case 't':
        {
            int testin = 0;
            do{
                std::cout << "\n\n Wielokrotne testowanie algorytmu, podaj ilosc prob: ";
                std::cin >> testin;
                if(testin <= 0) std::cout << "\n liczba prob musi byc wieksza od zera! Sprobuj ponownie!";
            }while(testin <= 0);

            for(int k = 0; k < testin; k++)
                std::cout << "\n\n " << genetical(kstropu, maxiteracja, ttime, wlkpopulacji, mkrzyzowania, mmutacji, wspkrzyzowania, wspmutacji);
        }
        case '0':
            break;
        default:
            {
            std::cout << " \nZly wybor, sprobuj ponownie";
            break;
            }
        }
    }
}

int genetical(int kstropu, int maxiteracja, int ttime, int wlkpopulacji, char mkrzyzowania, char mmutacji, int wspkrzyzowania, int wspmutacji)
{
//    std::cout << "\n" <<  kstropu;
//    std::cout << "\n" <<  maxiteracja;
//    std::cout << "\n" <<  ttime;
//    std::cout << "\n" <<  wlkpopulacji;
//    std::cout << "\n" <<  mkrzyzowania;
//    std::cout << "\n" <<  mmutacji;
//    std::cout << "\n" <<  wspkrzyzowania;
//    std::cout << "\n" <<  wspmutacji;

    int bestCost = INT_MAX;
    int iteracja = 0;
    bool robdalej = true;
    clock_t begin = clock();
    std::clock_t end = clock();

    

    do
    {
        iteracja++;








        end = clock();
        if(kstropu == '1' && double(end - begin) / CLOCKS_PER_SEC > ttime || kstropu == '3' && double(end - begin) / CLOCKS_PER_SEC > ttime)
            {robdalej = false;
            std::cout << " warunek czasu " << iteracja;
            }
        if(kstropu == '2' && iteracja >= maxiteracja || kstropu == '3' && iteracja >= maxiteracja)
            {robdalej = false;
            std::cout << " warunek iteracji " << iteracja;
            }
    }
    while(robdalej == true);

    std::cout<<"\n\n\nCzas wykonania proby: " << double(end - begin) / CLOCKS_PER_SEC;


    return bestCost;
}
