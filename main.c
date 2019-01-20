// Dodatkowe rzeczy:
//- pierwsze 1/3 sekwencji miast jest generowana losowo, reszta za pomocą Greedy


#include <fstream>
#include <iostream>
#include <conio.h>
#include <cmath>
#include <math.h>
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
    int kstopu = '2';
    int maxiteration = 1000;
    int ttime = 4;
    int popSize = 50;
    char mkrzyzowania = '1';
    char mmutacji = '1';
    int wspkrzyzowania = 80;
    int wspmutacji = 1;

    int choice = -1;
    while(choice != '0')
    {
        std::cout << "\n\n\n Aktualnie ustawione parametry programu: ";
        if(kstopu == '1' || kstopu == '3') std::cout << "\n Czas jednego wykonania algorytmu (w sekundach): " << ttime;
        if(kstopu == '3') std::cout << " lub gdy sie wykona";
        if(kstopu == '2' || kstopu == '3') std::cout << "\n maskymalna ustawiona liczba iteracji: " << maxiteration;
        if(mkrzyzowania == '1') std::cout << "\n Metoda krzyzowania: OX";
        if(mkrzyzowania == '2') std::cout << "\n Metoda krzyzowania: PMX";
        std::cout << "\n Wspolczynnik krzyzowania: " << wspkrzyzowania;
        if(mmutacji == '1') std::cout << "\n Metoda mutacji: insert";
        if(mmutacji == '2') std::cout << "\n Metoda mutacji: invert";
        if(mmutacji == '3') std::cout << "\n Metoda mutacji: swap";
        std::cout << "\n Wspolczynnik mutacji: " << wspmutacji;
        std::cout << "\n Wielkosc populacji: " << popSize;

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
                kstopu = getche();
                if(kstopu == '1' || kstopu == '3')
                    do
                    {
                        std::cout << "\n\n Podaj czas wykonywania algorytmu (w sekundach): ";
                        std::cin >> ttime;
                        if(ttime <= 0) std::cout << "\n Czas wykonywania musi byc wiekszy od zera! Sprobuj ponownie!";
                    }while(ttime <=0);
                if(kstopu == '2' || kstopu == '3')
                    do
                    {
                        std::cout << "\n\n Podaj maksymalna liczbe iteracji programu: ";
                        std::cin >> maxiteration;
                        if(maxiteration <= 0) std::cout << "\n Liczba iteracji musi byc wieksza od zera! Sprobuj ponownie!";
                    }while(maxiteration <= 0);
                if(kstopu != '1' && kstopu != '2' && kstopu != '3') std::cout << "\n\n Sprobuj jeszcze raz wybrac warunek zakonczenia dzialania algorytmu!";
            } while (kstopu != '1' && kstopu != '2' && kstopu != '3');
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
        case '8':
        {
            do {
                std::cout << "\n\n Podaj wielkosc populacji (zakres testowy: 10 - 500): ";
                std::cin >> popSize;
                if(popSize < 10 || popSize > 500) std::cout << "\n Wielkosc nie miesci sie w zakresie! Sprobuj ponownie!";
            } while (popSize < 10 || popSize > 500);
            break;
        }
        case '7':
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

            std::cout << "\n\n " << genetical(kstopu, maxiteration, ttime, popSize, mkrzyzowania, mmutacji, wspkrzyzowania, wspmutacji);
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
                std::cout << "\n\n " << genetical(kstopu, maxiteration, ttime, popSize, mkrzyzowania, mmutacji, wspkrzyzowania, wspmutacji);
        }
        case '0':
        {
            for(int i=0;i<cityamount;++i)        // zwolnij pamiec
                delete[] distances[i];
            delete[] distances;
            break;
        }
        default:
            {
            std::cout << " \nZly wybor, sprobuj ponownie";
            break;
            }
        }
    }
}

int genetical(int kstopu, int maxiteration, int ttime, int popSize, char mkrzyzowania, char mmutacji, int wspkrzyzowania, int wspmutacji)
{
//    std::cout << "\n" <<  kstopu;
//    std::cout << "\n" <<  maxiteration;
//    std::cout << "\n" <<  ttime;
//    std::cout << "\n" <<  popSize;
//    std::cout << "\n" <<  mkrzyzowania;
//    std::cout << "\n" <<  mmutacji;
//    std::cout << "\n" <<  wspkrzyzowania;
//    std::cout << "\n" <<  wspmutacji;

    int bestCost = INT_MAX;
    std::cout << "\n " << bestCost;
    int iteration = 0;
    bool keepGoing = true;
    clock_t begin = clock();
    std::clock_t end = clock();

    int amountOfRandom = std::max(cityamount / 3, 3);
    int tempR, tempV, temp, fA, tA;
    std::cout << "\n\n" << amountOfRandom << "\n\n";

    int* specimenValue = new int[popSize];
    for(int i = 0; i < popSize; i++)
        specimenValue[i] = 0;

    bool* visited = new bool[cityamount + 1];            //stworzenie tablicy mowiacej czy dana liczba juz wystapila w sekwencji
    visited[0] = visited[cityamount] = true;              //podpisanie pierwszego i ostatniego elementu jako juz wykonanego

    int** specimenP = new int* [popSize];               // dwuwymiarowa tablica dynamiczna okreslajaca sciezki osobnikow
    for(int i = 0; i < popSize; ++i)
    {
        specimenP[i] = new int[cityamount + 1];
        specimenP[i][0] = specimenP[i][cityamount] = 0;     //ustawienie pierwszego miasta jako poczatkowego i koncowego
//        int calculated = 0;

        for(int j = 1; j < cityamount; j++)                 //podpisanie miast jako niewykorzystanych w sciezce
            visited[j] = false;

        for (int j = 1; j < amountOfRandom; j++){               //wykonywanie kolejnych miejsc sekwencji w losowy sposób
            fA = tA = 0;
            tempR = (rand() % (cityamount - j)) + 1;        //tempR przyjmuje wartosc losowa z zakresu od 1 do ilosci miejsc pozostalych do zapisu
            for(int p = 1; fA < tempR; p++){                //wykonanie petli tak dlugo, az znajdziemy tyle miejsc nieprzypisanych ile chce nasza wartosc tempR
                if(visited[p] == false)                      //jesli wartosc jeszcze nie wystapila to zwiekszamy falseAmount, potrzebna nam jest wartosc liczby z randa
                    fA++;
                else                                        //jesli wartosc juz wystapila to zwiekszamy trueAmount, musimy wiedziec ile liczb skipowalismy aby dodac potem ta ilosc do wpisywanej liczby
                    tA++;
            }

            visited[tempR + tA] = true;                      //wpisanie liczby do sekwencji oraz oznaczenie jej jako wykorzystanej
            specimenP[i][j] = tempR + tA;
            specimenValue[i] += distances[specimenP[i][j-1]][specimenP[i][j]];
//            calculated++;
        }
        for(int j = amountOfRandom; j < cityamount; j++)        //GreedyAlgoritm
        {
            tempV = INT_MAX;
            for(int p = 1; p < cityamount; p++)
                if(visited[p] == false && distances[specimenP[i][j-1]][p] < tempV){
                    tempV = distances[specimenP[i][j-1]][p];
                    temp = p;
                }
            visited[temp] = true;
            specimenP[i][j] = temp;
            specimenValue[i] += distances[specimenP[i][j-1]][specimenP[i][j]];
//            calculated++;
        }
        specimenValue[i] += distances[specimenP[i][cityamount - 1]][specimenP[i][cityamount]];
//            std::cout << "\n\n nr liczby w sekwencji: " << i << "\n calculated: " << calculated + 1 << "\n distance: " << specimenValue[i] << "\nsequence of visit: ";
//            for(int u = 0; u <= cityamount; u++)
//                std::cout << " " << specimenP[i][u];
    }

    do
    {
        iteration++;








        end = clock();
        if(kstopu == '1' && double(end - begin) / CLOCKS_PER_SEC > ttime || kstopu == '3' && double(end - begin) / CLOCKS_PER_SEC > ttime)
            {keepGoing = false;
            std::cout << "\n warunek czasu " << iteration;
            }
        if(kstopu == '2' && iteration >= maxiteration || kstopu == '3' && iteration >= maxiteration)
            {keepGoing = false;
            std::cout << "\n warunek iteracji " << iteration;
            }
    }
    while(keepGoing);

    std::cout<<"\n\n\nCzas wykonania proby: " << double(end - begin) / CLOCKS_PER_SEC;

    delete[] visited;
    for(int i = 0; i < popSize; ++i)        // zwolnij pamiec
        delete[] specimenP[i];
    delete[] specimenP;

    return bestCost;
}
