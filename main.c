// Dodatkowe rzeczy:
//- sukcesja on/off
//- pierwsze 1/3 sekwencji miast jest generowana losowo, reszta za pomocą Greedy
//- 3 metody selekcji rodzicow: ruletka, losowa, turniejowa,
//- 2 metody krzyzowania: PMX, HX
//- 3 metody mutacji: insert, invert, swap
//- 3 metody selekcji osobnikow: ruletka, ranking, turniej
//- 2 warunki stopu: czas, ilosc iteracji

// blad we wzorze na prawdopodobienstwo w prezentacji dr Kaplona

#include <fstream>
#include <iostream>
#include <conio.h>
#include <cmath>
#include <math.h>
#include <ctime>


int cityamount = 0;
int **distances;


void chosingfile();
bool fileread(std::string);
void writetab(int**);
void genmenu();
int genetical(int, int, int, int, int, char, char, char, char, int, int, int, int, int, bool, char, int);
int mrowki();


int  main()
{
    srand(time(NULL));
    chosingfile();
    genmenu();

//    getche();
}

void chosingfile()                          // menu wybierania plikow do odczytu
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

void writetab(int** cities)                 // wypisywanie aktualnej macierzy przejsc miedzy miastami
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

void genmenu()
{
    bool sukcesja = false;
    int kstopu = '2';
    int maxiteration = 1;
    int ttime = 4;
    int popSize = 10;
    int popChild = 4;
    char mkrzyzowania = '1';
    char mmutacji = '4';
    char mselekcji = '2';
    char mrodzica = '1';
    int wspkrzyzowania = 80;
    int wspmutacji = 1;
    int wspselekcji = 10;
    int wsprodzica = 250;
    int maxmutacji = 1;
    char mmemetic = '1';
    int wspmemetic = 10;

    int choice = -1;
    char choice2;
    while(choice != '0')
    {
        std::cout << "\n\n\n Aktualnie ustawione parametry programu: ";
        if(kstopu == '1' || kstopu == '3') std::cout << "\n Czas jednego wykonania algorytmu (w sekundach): " << ttime;
        if(kstopu == '3') std::cout << " lub gdy sie wykona";
        if(kstopu == '2' || kstopu == '3') std::cout << "\n maskymalna ustawiona liczba iteracji: " << maxiteration;
        if(mkrzyzowania == '1') std::cout << "\n Metoda krzyzowania: OX";
        if(mkrzyzowania == '2') std::cout << "\n Metoda krzyzowania: PMX";
        if(mkrzyzowania == '3') std::cout << "\n Metoda krzyzowania: HX";
//        std::cout << "\n Wspolczynnik krzyzowania: " << wspkrzyzowania;
        if(mmutacji == '1') std::cout << "\n Metoda mutacji: insert";
        if(mmutacji == '2') std::cout << "\n Metoda mutacji: invert";
        if(mmutacji == '3') std::cout << "\n Metoda mutacji: swap";
        std::cout << "\n Wspolczynnik mutacji: " << wspmutacji;
        std::cout << "\n Maksymalna ilosc mutacji: " << maxmutacji;
        if(mselekcji == '1') std::cout << "\n Metoda selekcji osobnikow: kola ruletki";
        if(mselekcji == '2') std::cout << "\n Metoda selekcji osobnikow: rankingowa";
        if(mselekcji == '3') std::cout << "\n Metoda selekcji osobnikow: turniejowa\n Wielkosc turnieju: " << wspselekcji;
//        if(mselekcji == '4') std::cout << "\n Metoda selekcji osobnikow: rangowa";
        if(mrodzica == '1') std::cout << "\n Metoda selekcji rodzicow: kola ruletki";
        if(mrodzica == '2') std::cout << "\n Metoda selekcji rodzicow: losowa";
        if(mrodzica == '3') std::cout << "\n Metoda selekcji rodzicow: turniejowa\n Wielkosc turnieju: " << wsprodzica;
//        if(mrodzica == '4') std::cout << "\n Metoda selekcji rodzicow: rangowa";
        std::cout << "\n Wielkosc populacji: " << popSize;
        std::cout << "\n Ilosc potomkow w kazdym pokoleniu populacji: " << popChild;
        if(sukcesja == false) std::cout << "\n Sukcesja: wylaczona";
        if(sukcesja == true) std::cout << "\n Sukcesja: wlaczona";

        std::cout << "\n\n Wybierz opcje do rozwiazania TSP:";
        std::cout << "\n1. Wybierz nowy plik z danymi";
        std::cout << "\n2. Wyswietl aktualnie wczytany plik";
        std::cout << "\n3: Ustaw Kryterium Stopu";
        std::cout << "\n4: Ustaw Metode I Wspolczynnik Krzyzowania";
        std::cout << "\n5: Ustaw Metode I Wspolczynnik Mutacji";
        std::cout << "\n6: Ustaw Metode Selekcji Osobnikow";
        std::cout << "\n7: Ustaw Metode Selekcji Rodzicow";
        std::cout << "\n8. Ustaw Wielkosc Populacji";
        std::cout << "\n9: Algorytm Genetyczny";
        std::cout << "\n0. Wyjscie ";
        std::cout << "\nt. Wielokrotne Testowanie Algorytmu";
        std::cout << "\na. Wybieranie Algorytmu Memetycznego";
        std::cout << "\nm. Algorytm Mrowkowy";
        std::cout << "\nTwoj wybor: ";

        choice = getche();
        switch(choice)
        {
        case '1':{  //wczytaj plik
            for(int i=0;i<cityamount;++i)        // zwolnij pamiec
                delete[] distances[i];
            delete[] distances;
            std::cout <<"\n\n";
            chosingfile();
            break;
        }
        case '2':{  //wypisz plik
            std::cout << " \nZawarte w nim dane to: \n";
            writetab(distances);
            break;
        }
        case '3':{  //kryterium stopu
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
        case '4':{  //krzyzowanie
            do {
                std::cout << "\n\n Wybierz metode krzyzowania z ponizszych: ";
                std::cout << "\n 1. OX";
                std::cout << "\n 2. PMX";
                std::cout << "\n 3. HX";
                std::cout << "\n Twoj wybor: ";
                mkrzyzowania = getche();
                if(mkrzyzowania != '1' && mkrzyzowania != '2' && mkrzyzowania != '3') std::cout << "\n Nie ma takiej metody! Sprobuj ponownie!";
            } while (mkrzyzowania != '1' && mkrzyzowania != '2' && mkrzyzowania != '3');
//            do {
//                std::cout << "\n\n Podaj wartosc wspolczynnika krzyzowania: ";
//                std::cin >> wspkrzyzowania;
//                if(wspkrzyzowania <= 0) std::cout << "\n Wspolczynnik krzyzowania musi byc wiekszy od zera! Sprobuj ponownie!";
//            } while (wspkrzyzowania <=0);
            break;
        }
        case '5':{  //mutacja
            do {
                std::cout << "\n\n Wybierz metode mutacji z ponizszych: ";
                std::cout << "\n 1. insert";
                std::cout << "\n 2. invert";
                std::cout << "\n 3. swap";
                std::cout << "\n 4. brak mutacji";
                std::cout << "\n Twoj wybor: ";
                mmutacji = getche();
                if(mmutacji != '1' && mmutacji != '2' && mmutacji != '3' && mmutacji != '4') std::cout << "\n Nie ma takiej metody! Sprobuj ponownie!";
            } while (mmutacji != '1' && mmutacji != '2' && mmutacji != '3' && mmutacji != '4');
            do {
                std::cout << "\n\n Podaj wartosc wspolczynnika mutacji (zakres 0-100): ";
                std::cin >> wspmutacji;
                if(wspmutacji < 0 || wspmutacji > 100) std::cout << "\n Wspolczynnik mutacji musi byc wiekszy od zera! Sprobuj ponownie!";
            } while (wspmutacji <0 || wspmutacji > 100);
            if(mmutacji == '1' || mmutacji == '2' || mmutacji == '3')
                do {
                    std::cout << "\n\n Podaj maksymalna ilosc mutacji na pokolenie (od 0 do 10): ";
                    std::cin >> maxmutacji;
                    if(maxmutacji < 0 || maxmutacji > 10) std::cout << "\n Wspolczynnik mutacji musi byc wiekszy od zera! Sprobuj ponownie!";
                } while (maxmutacji < 0 || maxmutacji > 10);
            break;
        }
        case '6':{  //fitness function selection
            do {
                std::cout << "\n\n Wybierz metode selekcji osobnikow na podstawie FitnessFunction z ponizszych: ";
                std::cout << "\n 1. kola ruletki";
                std::cout << "\n 2. rankingowa";
                std::cout << "\n 3. turniejowa";
//                std::cout << "\n 4. rangowa";
                std::cout << "\n Twoj wybor: ";
                mselekcji = getche();
                if(mselekcji != '1' && mselekcji != '2' && mselekcji != '3'/* && mselekcji != '4'*/) std::cout << "\n Nie ma takiej metody! Sprobuj ponownie!";
            } while (mselekcji != '1' && mselekcji != '2' && mselekcji != '3'/* && mselekcji != '4'*/);
             if(mselekcji == '3')
                do{
                    std::cout << "\n\n Wybierz wielkosc turnieju (zakres 1 - " << (popSize/2) - 1 << "): ";
                    std::cin >> wspselekcji;
                    if(wspselekcji < 1 && wspselekcji >= (popSize /2)) std::cout << "\n Podaj wartosc z zakresu!";
                }while(wspselekcji < 1 && wspselekcji >= (popSize /2));
            break;
        }
        case '7':{  //wybor rodzicow
            do {
                std::cout << "\n\n Wybierz metode selekcji rodzicow z ponizszych: ";
                std::cout << "\n 1. kola ruletki";
                std::cout << "\n 2. losowa";
                std::cout << "\n 3. turniejowa";
//                std::cout << "\n 4. rangowa";
                std::cout << "\n Twoj wybor: ";
                mrodzica = getche();
                if(mrodzica != '1' && mrodzica != '2' && mrodzica != '3') std::cout << "\n Nie ma takiej metody! Sprobuj ponownie!";
            } while (mrodzica != '1' && mrodzica != '2' && mrodzica != '3');
            if(mrodzica == '3')
                do{
                    std::cout << "\n\n Wybierz wielkosc turnieju (zakres 1 - " << (popSize/2) - 1 << "): ";
                    std::cin >> wsprodzica;
                    if(wsprodzica < 1 && wsprodzica >= (popSize /2)) std::cout << "\n Podaj wartosc z zakresu!";
                }while(wsprodzica < 1 && wsprodzica >= (popSize /2));
            break;
        }
        case '8':{  //wielkosc populacji
            do {
                std::cout << "\n\n Podaj wielkosc populacji (zakres testowy: 10 - 5000): ";
                std::cin >> popSize;
                if(popSize < 10 || popSize > 5000) std::cout << "\n Wielkosc nie miesci sie w zakresie! Sprobuj ponownie!";
            } while (popSize < 10 || popSize > 5000);
            do {
                std::cout << "\n\n Podaj ilosc potomkow na pokolenie (zakres: 10 - 5000): ";
                std::cin >> popChild;
                if(popChild < 10 || popChild > 5000) std::cout << "\n Wielkosc nie miesci sie w zakresie! Sprobuj ponownie!";
            } while (popChild < 10 || popChild > 5000);

            std::cout << "\n Czy chcesz zamienic wieklkosc turnieju na 1/4 wielkosci populacji = " << popSize / 4 << " ?? (y = tak) ";
            choice2 = getche();
            if(choice2 == 'y')
                wsprodzica = wspselekcji = popSize / 4;
            break;
        }
        case '9':{  //AG exe
            if((sukcesja == true && popSize >= popChild) || (mrodzica == '3' && wsprodzica >= (popSize/2)) || (mselekcji == '3' && wspselekcji >= (popSize/2)))
                std::cout << "\n\n\ Jakis warunek jest popsuty, wprowadz poprawne dane! \n";
            else
                std::cout << "\n\n " << genetical(kstopu, maxiteration, ttime, popSize, popChild, mkrzyzowania, mmutacji, mselekcji, mrodzica, wspkrzyzowania, wspmutacji, wspselekcji, wsprodzica, maxmutacji, sukcesja, mmemetic, wspmemetic);
            break;
        }
        case 't':{  //multi AG exes
            int testin = 0;
            do{
                std::cout << "\n\n Wielokrotne testowanie algorytmu, podaj ilosc prob: ";
                std::cin >> testin;
                if(testin <= 0) std::cout << "\n liczba prob musi byc wieksza od zera! Sprobuj ponownie!";
            }while(testin <= 0);

            clock_t begin = clock();
            std::clock_t end = clock();
            for(int k = 0; k < testin; k++)
                std::cout << "\n\n " << genetical(kstopu, maxiteration, ttime, popSize, popChild, mkrzyzowania, mmutacji, mselekcji, mrodzica, wspkrzyzowania, wspmutacji, wspselekcji, wsprodzica, maxmutacji, sukcesja, mmemetic, wspmemetic);
            std::cout<<"\n\n\nCzas wykonania proby: " << double(end - begin) / CLOCKS_PER_SEC;
            break;
        }
        case 'a':{  //MemeticAlgoritm
            do {
                std::cout << "\n\n Wybierz metode wykonania algorytmu memetycznego z ponizszych: ";
                std::cout << "\n 1. insert";
                std::cout << "\n 2. swap";
                std::cout << "\n Twoj wybor: ";
                mmutacji = getche();
                if(mmemetic != '1' && mmemetic != '2' && mmemetic != '3') std::cout << "\n Nie ma takiej metody! Sprobuj ponownie!";
            } while (mmemetic != '1' && mmemetic != '2' && mmemetic != '3');
            do {
                std::cout << "\n\n Podaj wartosc wspolczynnika mutacji (zakres 0-100): ";
                std::cin >> wspmutacji;
                if(wspmemetic <= 0 || wspmemetic >= 100) std::cout << "\n Wspolczynnik mutacji musi byc wiekszy od zera! Sprobuj ponownie!";
            } while (wspmemetic <= 0 || wspmemetic >= 100);;
            break;
        }
        case 'm':{  //mrowki!
            std::cout << "\n\n znaleziono: " << mrowki();
            break;
        }
        case 's':{
            sukcesja = !sukcesja;
            break;
        }
        case '0':{  //exit
            for(int i=0;i<cityamount;++i)        // zwolnij pamiec
                delete[] distances[i];
            delete[] distances;
            break;
        }
        default:{
            std::cout << " \nZly wybor, sprobuj ponownie";
            break;
            }
        }
    }
}

int genetical(int kstopu, int maxiteration, int ttime, int popSize, int popChild, char mkrzyzowania, char mmutacji, char mselekcji, char mrodzica, int wspkrzyzowania, int wspmutacji, int wspselekcji, int wsprodzica, int maxmutacji, bool sukcesja, char mmemetic, int wspmemetic)
{


//    std::cout << "\n" <<  kstopu;
//    std::cout << "\n" <<  maxiteration;
//    std::cout << "\n" <<  ttime;
//    std::cout << "\n" <<  popSize;
//    std::cout << "\n" <<  popChild;
//    std::cout << "\n" <<  mkrzyzowania;
//    std::cout << "\n" <<  mmutacji;
//    std::cout << "\n" <<  mselekcji;
//    std::cout << "\n" <<  wspkrzyzowania;
//    std::cout << "\n" <<  wspmutacji;
//    std::cout << "\n" <<  wspmutacji;
//    std::cout << "\n" <<  wsprodzica;
//    std::cout << "\n" <<  maxmutacji;

    int succession = 0;
    if(sukcesja == true)
        succession = popSize;
    int bestCost = INT_MAX;
    int iteration = 0;
    bool keepGoing = true;
    clock_t begin = clock();
    std::clock_t end = clock();
    int specimenMaxValue = 0;

    int amountOfRandom = cityamount / 3;
    if(amountOfRandom < 3) amountOfRandom = 3;
    int tempR, tempV, temp, fA, tA, allPaths, tmp, tmp2, k1, k2, x, esc, loc1, loc2;
//    std::cout << "\n\n" << amountOfRandom << "\n\n";
    int* cityOperator = new int[cityamount + 1];
    int* allPopOperator = new int[popSize + popChild];//////////////////////////////////////////////////////////////////////////////////////////////
    int* bestPath = new int[cityamount + 1];
    int* specimenValue = new int[popSize];
    for(int i = 0; i < popSize; i++)
        specimenValue[i] = 0;

    bool* bAllPop = new bool[popSize + popChild];
    bool* bAllPop2 = new bool[popSize + popChild];
//    bool* bPopSize = new bool[popSize];
//    bool* bPopChild = new bool[popChild];
    bool* bCity = new bool[cityamount + 1];            //stworzenie tablicy mowiacej czy dana liczba juz wystapila w sekwencji
    bCity[0] = bCity[cityamount] = true;              //podpisanie pierwszego i ostatniego elementu jako juz wykonanego
    cityOperator[0] = cityOperator[cityamount] = 0;

    int** newGeneration = new int* [popChild];               // dwuwymiarowa tablica dynamiczna okreslajaca sciezki osobnikow przyszlej generacji
    int* childValue = new int[popChild];
    int** newParents = new int* [((popChild / 2)+(popChild % 2))];

    for(int i = 0; i < ((popChild / 2)+(popChild % 2)); i++)
    newParents[i] = new int[2];

    for(int i = 0; i < popChild; ++i)
    {
        childValue[i] = 0;
        newGeneration[i] = new int[cityamount + 1];
        for(int j = 0; j <= cityamount; j++)
            newGeneration[i][j] = 0;
    }




    int** oldGeneration = new int* [popSize];       // dwuwymiarowa tablica dynamiczna okreslajaca sciezki osobnikow juz obecnej generacji
    for(int i = 0; i < popSize; ++i)                // tworzenie pierwszego pokolenia
    {
        oldGeneration[i] = new int[cityamount + 1];
        oldGeneration[i][0] = oldGeneration[i][cityamount] = 0;     //ustawienie pierwszego miasta jako poczatkowego i koncowego

        for(int j = 1; j < cityamount; j++)                 //podpisanie miast jako niewykorzystanych w sciezce
            bCity[j] = false;

        for (int j = 1; j < amountOfRandom; j++){               //wykonywanie kolejnych miejsc sekwencji w losowy sposób
            fA = tA = 0;
            tempR = (rand() % (cityamount - j)) + 1;        //tempR przyjmuje wartosc losowa z zakresu od 1 do ilosci miejsc pozostalych do zapisu
            for(int p = 1; fA < tempR; p++){                //wykonanie petli tak dlugo, az znajdziemy tyle miejsc nieprzypisanych ile chce nasza wartosc tempR
                if(bCity[p] == false)                      //jesli wartosc jeszcze nie wystapila to zwiekszamy falseAmount, potrzebna nam jest wartosc liczby z randa
                    fA++;
                else                                        //jesli wartosc juz wystapila to zwiekszamy trueAmount, musimy wiedziec ile liczb skipowalismy aby dodac potem ta ilosc do wpisywanej liczby
                    tA++;
            }

            bCity[tempR + tA] = true;                      //wpisanie liczby do sekwencji oraz oznaczenie jej jako wykorzystanej
            oldGeneration[i][j] = tempR + tA;
//            specimenValue[i] += distances[oldGeneration[i][j-1]][oldGeneration[i][j]];
        }
        for(int j = amountOfRandom; j < cityamount; j++)        //GreedyAlgoritm
        {
            tempV = INT_MAX;
            for(int p = 1; p < cityamount; p++)
                if(bCity[p] == false && distances[oldGeneration[i][j-1]][p] < tempV){
                    tempV = distances[oldGeneration[i][j-1]][p];
                    temp = p;
                }
            bCity[temp] = true;
            oldGeneration[i][j] = temp;
//            specimenValue[i] += distances[oldGeneration[i][j-1]][oldGeneration[i][j]];
        }
//        specimenValue[i] += distances[oldGeneration[i][cityamount - 1]][0];
        specimenValue[i] = 0;
        for(int j = 0; j < cityamount; j++){
            specimenValue[i] += distances[oldGeneration[i][j]][oldGeneration[i][j+1]];
//            std::cout << "\n Przejscie z " << oldGeneration[i][j] << " do " << oldGeneration[i][j + 1] << " generuje: " << distances[oldGeneration[i][j]][oldGeneration[i][j+1]];
        }

        if(specimenValue[i] < bestCost)
        {
            bestCost = specimenValue[i];
            for(int j = 0; j <= cityamount; j++)
                bestPath[j] = oldGeneration[i][j];
        }
//            std::cout << "\n\n nr liczby w sekwencji: " << i << "\n distance: " << specimenValue[i] << "\nsequence of visit: ";
//            for(int u = 0; u <= cityamount; u++)
//                std::cout << " " << oldGeneration[i][u];
    }

    do
    {
        iteration++;

//        std::cout << "\n switch: " << iteration;
        switch(mrodzica){

            case '1':{  //kola ruletki
                allPaths = 0;

                for(int i = 0; i < popSize; i++)            //znajdowanie najdluzszej sciezki w populacji
                    if(specimenValue[i] > specimenMaxValue)
                        specimenMaxValue = specimenValue[i];
//                std::cout << "\n sMax: " << specimenMaxValue;

                for(int i = 0; i < popSize; i++)            //obliczanie szansy na rozmnozenie na podstawie wartosci o ktora jest osobnik lepszy od najgorszej sciezki
                    allPaths += (specimenMaxValue - specimenValue[i] + 1);

//                std::cout << "\n maxVal: " << specimenMaxValue << "  allpaths: " << allPaths;


                for(int i = 0; i < ((popChild / 2) + (popChild % 2)); i++)
                {

                    x = 0;
                    temp = -1;
                                                                // stworzenie wartosci bedacej suma wszystkich mozliwych szans dla osobnikow na
                    do{                                         // zostanie rodzicami (bycie lepszym od najgorszego o dana wartosc +1). nastepuje
                        tmp = rand() % allPaths;                // wylosowanie wartosci a nastepnie jest sprawdzane w ktorym osobniku znajduje sie wylosowana
                        tmp2 = 0;                               // szansa. Nastepnie jego wartosc jest odejmowana z puli i losuje sie jeszcze raz z jego pominieciem
//                        std::cout << "\nszukam: " << i << x;
                        for(int j = 0; tmp2 < tmp; j++)
                        {
                            tmp2 += (specimenMaxValue - specimenValue[j] + 1);
                            if(tmp2 >= tmp){
                                newParents[i][x] = j;
//                                std::cout << "\n tmp: " << tmp << " tmp2: " << tmp2 << " maxrand: " << allPaths << " specimenMaxValue: " << specimenMaxValue << " specimenValue[j]: "  << specimenValue[j];
                            }
                        }
//                        if(tmp2 > tmp + 1000000){     //sprawdzenie
//                            std::cout << "\n";
//                            for(int w = 0; w <= cityamount; w++)
//                                std::cout << " " << oldGeneration[i][w];
//                            std::cout << " value: " << specimenValue;
//                        }
                        x = 1;
                        temp++;
                    }while(newParents[i][0] == newParents[i][1] || temp <= 0);      // do-while wymusza pierwsze przejscie, temp = 0 zatrzymuje na drugie


//                    tmp = rand() % (allPaths - specimenValue[newParents[i][0]] - 1);
//                    tmp2 = 0;
//                    for(int j = 0; tmp2 < tmp; j++)
//                    {
//                        if(j == newParents[i][0]) j++;
//                            tmp2 += (specimenMaxValue - specimenValue[j] + 1);
//                        if(tmp2 >= tmp){
//                            newParents[i][1] = j;
//                            std::cout << "\n tmp: " << tmp << " tmp2: " << tmp2 << " maxrand: " << (allPaths - specimenValue[newParents[i][0]] - 1) << " specimenMaxValue: " << specimenMaxValue << " specimenValue[j]: "  << specimenValue[j];;
//                        }
//                    }
//                    if(tmp2 > tmp + 10000){     //sprawdzenie
//                        std::cout << "\n";
//                        for(int w = 0; w <= cityamount; w++)
//                            std::cout << " " << oldGeneration[i][w];
//                        std::cout << " value: " << specimenValue;
//                    }

                    if(newParents[i][1] >= popSize || newParents[i][0] >= popSize)
                        std::cout << "\n\n POPSULEM SELEKCJA RULETKA \n\n";
                }
//                for(int i = 0; i< popChild; i++)
//                    std::cout << "\n parent: " << newParents[i][0] << " " << newParents[i][1];
                break;
            }
            case '2':{  //losowa
                for(int i = 0; i < ((popChild / 2) + (popChild % 2)); i++)
                {
                    newParents[i][0] = rand() % popSize;
                    newParents[i][1] = rand() % (popSize - 1);
                    if(newParents[i][0] <= newParents[i][1])
                        newParents[i][1]++;

                    if(newParents[i][1] >= popSize || newParents[i][0] >= popSize)
                        std::cout << "\n\n\n\n\n\n POPSULEM SELEKCJA LOSOWA \n\n\n\n\n\n";

                }
//                for(int i = 0; i< popChild; i++)
//                    std::cout << "\n parent: " << newParents[i][0] << " " << newParents[i][1];
                break;
            }
            case '3':{  //turniejowa
                for(int i = 0; i < ((popChild / 2) + (popChild % 2)); i++)
                {
                    for(int j = 0; j < popSize; j++)    //zerowanie tablicy
                        bAllPop[j] = false;

                    x = 0;
                    do{
                        temp = INT_MAX;   // to bedzie najlepsza znaleziona wartosc
                        for(int j = 0; j < wsprodzica; j++)
                        {
                            do{
                                tmp = rand() % popSize;
                            }while(bAllPop[tmp] == true);
                            bAllPop[tmp] = true;

                            if(specimenValue[tmp] < temp){
                                temp = specimenValue[tmp];
                                tmp2 = tmp;
                            }
                        }
                        newParents[i][x] = tmp2;
                        x++;
                    }while(x <= 1);
                }

                for(int i = 0; i < ((popChild / 2) + (popChild % 2)); i++){
//                    std::cout << "\n " << newParents[i][0] << "  " << newParents[i][1];
                    if(newParents[i][0] == newParents[i][1])
                        std::cout << "\n\n\n\n POPSULEM TURNIEJ \n\n\n\n";
                }

                break;
            }
//            case '4':{  //rangowa liniowa
//
//                break;
//            }
        }


//        std::cout << "\n krzyzowanie: " << iteration;
        switch(mkrzyzowania){
            case '1':{ //OX
                for(int i = 0; i < ((popChild / 2) + (popChild % 2)); i++)
                {
                    loc1 = rand() % (cityamount - 1) + 1;         //wylosowanie locusow
                    loc2 = rand() % (cityamount - 1) + 1;
                    if(loc1 > loc2){
                        temp = loc1;                              //ustawienie ich w kolejnosci
                        loc1 = loc2;
                        loc2 = temp;
                    }
                    k1 = 0;             //rodzic numer 1 -> k1 = 0, k2 = 1 ; na koncu petli nastepuje zamiana miejsc
                    k2 = 1;
                    esc = 0;            //pomocniczy warunek petli dowhile, wymuszajacy 2 przejscia petli w normalnych okolicznosciach

                    do
                    {
                        for(int j = 1; j < cityamount; j++){        //zerowanie uzywanych tablic
                            bCity[j] = false;
                        }
                        for(int j = loc1; j <= loc2; j++){              // ustawienie przepisanych miast jako odwiedzonych
                            newGeneration[(i*2+k1)][j] = oldGeneration[newParents[i][k1]][j];
                            bCity[oldGeneration[newParents[i][k1]][j]] = true;
                        }
                        temp = loc2 + 1;
                        for(int j = (loc2 + 1); j < cityamount; j++)
                        {
                            if(bCity[oldGeneration[newParents[i][k1]][j]] == false)
                                {
                                    newGeneration[(i*2+k1)][temp] = oldGeneration[newParents[i][k1]][j];
                                    bCity[oldGeneration[newParents[i][k1]][j]] == true;
                                    temp++;
                                }
                        }

                        for(int j = 0; j < loc1; j++)
                        {
                            if(temp == cityamount)
                                temp = 1;

                            if(bCity[oldGeneration[newParents[i][k1]][j]] == false)
                                {
                                    newGeneration[(i*2+k1)][temp] = oldGeneration[newParents[i][k1]][j];
                                    bCity[oldGeneration[newParents[i][k1]][j]] == true;
                                    temp++;
                                }
                        }





                        temp = k1;      //zamiana rodzicow miejscami
                        k1 = k2;
                        k2 = temp;
                        esc++;
                    }while(esc <= 1 && i < (popChild / 2));

                }
                break;
            }
            case '3':{ //HX - bez breaka, hx jest metoda pmx z tylko jednym locusem, wiec ustawiajac locus pmx na ostatnia pozycje dziala tak samo!
                loc2 = cityamount - 1;
            }
            case '2':{ //PMX
//                std::cout << "\n\nPMX\n\n";
//
//                for(int i = 0; i < popSize; i++){
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << oldGeneration[i][u];
//                    std::cout << "  osobnik nr: " << i << "\n";}
//
//                for(int i = 0; i < popChild; i++){
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << newGeneration[i][u];
//                    std::cout << "  osobnik nr: " << i << "\n";}

                for(int i = 0; i < ((popChild / 2) + (popChild % 2)); i++)
                {
//                    std::cout << "\n krzyzowanie1: " << i;
                    loc1 = rand() % (cityamount - 1) + 1;         //wylosowanie locusow
                    if(mkrzyzowania != '3')
                    {
                        loc2 = rand() % (cityamount - 1) + 1;
                        if(loc1 > loc2){
                            temp = loc1;                              //ustawienie ich w kolejnosci
                            loc1 = loc2;
                            loc2 = temp;
                        }
                    }
                    k1 = 0;             //rodzic numer 1 -> k1 = 0, k2 = 1 ; na koncu petli nastepuje zamiana miejsc
                    k2 = 1;
                    esc = 0;            //pomocniczy warunek petli dowhile, wymuszajacy 2 przejscia petli w normalnych okolicznosciach


//                         for(int u = 0; u <= cityamount; u++)
//                            std::cout << " " << newGeneration[(i*2+k1)][u];
//                        std::cout << "  -pot00omek " << k1 << "\n";


                    do{
//                        std::cout << "\n krzyzowanie2: " << esc;
                        for(int j = 1; j < cityamount; j++){        //zerowanie uzywanych tablic
                            bCity[j] = false;
                            cityOperator[j] = 0;
                        }
                        for(int j = loc1; j <= loc2; j++){              // ustawienie przepisanych miast jako odwiedzonych
                            newGeneration[(i*2+k1)][j] = oldGeneration[newParents[i][k1]][j];
                            bCity[oldGeneration[newParents[i][k1]][j]] = true;
                        }

                        tmp = 0;        //ilosc liczb ktore nie zostaly przyporzadkowane w pierwszym ruchu
    //                    std::cout << "\nt3: " << tmp << "   rodzic: " << newParents[i][1] << "\n";
                        for(int j = loc1; j <= loc2; j++){      //sprawdzamy te same co przeniesione tylko z p2
//                            std::cout << "." << j;
                            tempV = oldGeneration[newParents[i][k2]][j];///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                            std::cout << "p";
                            if(bCity[tempV] == false){     //sprawdzenie ktore z wierzcholkow rodzica2 z tego przedzialu nie zostaly uzyte przy krzyzowaniu do potomka
//                                std::cout << "k";
                                cityOperator[j] = oldGeneration[newParents[i][k2]][j];
                                tmp++;
                            }
                        }
//
//                        std::cout << "\n\n WEJSCIOWY TMP: " << tmp << "\n\n";
//                        for(int u = 0; u <= cityamount; u++)
//                            std::cout << " " << newGeneration[(i*2+k1)][u];
//                        std::cout << "  - odwedzone miasta w potomku\n";
//                        for(int u = 0; u <= cityamount; u++)
//                            std::cout << " " << cityOperator[u];
//                        std::cout << "  - cityOperator\n\n";

    //                    std::cout << "\n tmp: " << tmp << " iteracja i: " << i;
                        tmp2 = 1;  // iterator dzialajacy jak petla w for
                        while(tmp > 0)//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        {   /*std::cout << "PMX4";*/
//                            std::cout << "\n krzyzowanie3: " << tmp <<" "<<tmp2;

//                    if(iteration > 1){
//                    std::cout << "\n\n loc1: " << loc1 << "  loc2: " << loc2 << "\n";
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << oldGeneration[newParents[i][k1]][u];
//                        std::cout << "  -rodzic1\n";
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << oldGeneration[newParents[i][k2]][u];
//                        std::cout << "  -rodzic2\n";
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << newGeneration[(i*2+k1)][u];
//                        std::cout << "  -potomek " << k1 << "\n";
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << bCity[u];
//                        std::cout << "  -odwedzone miasta\nsprawdzenie cO: ";
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << cityOperator[u];
//                        std::cout << "  -cityOperator ";}



                            if(cityOperator[tmp2] != 0)
                                for(int j = 1; j < cityamount; j++)
                                    if(oldGeneration[newParents[i][k1]][tmp2] == oldGeneration[newParents[i][k2]][j] && cityOperator[j] == 0)
                                    {
//                                        std::cout <<" j: " << j;


                                        cityOperator[j] = cityOperator[tmp2];
                                        cityOperator[tmp2] = 0;
                                        if(newGeneration[(i*2+k1)][j] == 0)
                                        {
//                                            std::cout <<"\n WSZEDLEM222!";
                                            newGeneration[(i*2+k1)][j] = cityOperator[j];
                                            tmp--;
                                            cityOperator[j] = 0;
                                        }
                                    }
    //                        std::cout << " tmp: " << tmp << "  tmp2: " << tmp2 << "  cityOperator: " << cityOperator[tmp2] << "\n";
                            tmp2++;
                            if(tmp2 == cityamount)
                                tmp2 = 1;
                        }

    //                    std::cout << "\n\n KONIECPMX\n\n";

    //                    for(int u = 0; u <= cityamount; u++)
    //                        std::cout << " " << newGeneration[(i*2+k1)][u];
    //                    std::cout << "  -potomek1\n";

                        for(int j = 1; j < cityamount; j++)         //dopisanie pozostalych sciezek
                            if(newGeneration[(i*2+k1)][j] == 0)
                                newGeneration[(i*2+k1)][j] = oldGeneration[newParents[i][k2]][j];

//                    std::cout << "\n\n loc1: " << loc1 << "  loc2: " << loc2 << "\n";
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << oldGeneration[newParents[i][k1]][u];
//                        std::cout << "  -rodzic1\n";
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << oldGeneration[newParents[i][k2]][u];
//                        std::cout << "  -rodzic2\n";
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << newGeneration[(i*2+k1)][u];
//                        std::cout << "  -potomek " << k1 << "\n";
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << bCity[u];
//                        std::cout << "  -odwedzone miasta\nsprawdzenie cO: ";
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << cityOperator[u];
//                        std::cout << "  -cityOperator ";

                    temp = k1;      //zamiana rodzicow miejscami
                    k1 = k2;
                    k2 = temp;
                    esc++;
                    }while(esc <= 1 && i < (popChild / 2));
                }
//                std::cout << "\nkrzyzowaniewyjsciepmx: " << iteration;
                break;
            }
        }


//
//        if(mmemetic == '1' || mmemetic == '2')          // algorytm memetyczny
//        {
//            for(int q = 0; q < popChild; q++){          // sprawdzany dla kazdego dziecka
//                tmp = INT_MAX; //Najmniejszy osiagniety przez nas wynik
////                std::cout << "\n stara sekwencja potomka nr: " << q << "    ";
////                for(int i = 0; i <= cityamount; i++)
////                    std::cout << " " << newGeneration[q][i];
//
//                for(int i = 1; i < cityamount-1; i++){
//                    for(int j = i+1; j < cityamount; j++){
//
//                        // wyliczanie roznicy w koszcie, obliczajac jedynie roznice miedzy sciezkami bedacymi czesciami zamienionych miast
//                        if((mmemetic == '2' && (i+1 == j)) || mmemetic == '1'){
//                            tmp2 = distances[newGeneration[q][i-1]][newGeneration[q][j]] + distances[newGeneration[q][j]][newGeneration[q][i]] + distances[newGeneration[q][i]][newGeneration[q][j+1]] - distances[newGeneration[q][i-1]][newGeneration[q][i]] - distances[newGeneration[q][i]][newGeneration[q][j]] - distances[newGeneration[q][j]][newGeneration[q][j+1]];
////                            std::cout << "\n " << i << "  " << j << "  cost: " << tmp2 << " = " << distances[newGeneration[q][i-1]][newGeneration[q][j]]  << " + " << distances[newGeneration[q][j]][newGeneration[q][i]] << " + " << distances[newGeneration[q][i]][newGeneration[q][j+1]] << " - " << distances[newGeneration[q][i-1]][newGeneration[q][i]] << " - " << distances[newGeneration[q][i]][newGeneration[q][j]] << " - " << distances[newGeneration[q][j]][newGeneration[q][j+1]];
//                        }
//                        if(mmemetic == '2' && (i+1 != j)){
//                            tmp2 = distances[newGeneration[q][i-1]][newGeneration[q][j]] + distances[newGeneration[q][j]][newGeneration[q][i+1]] + distances[newGeneration[q][j-1]][newGeneration[q][i]] + distances[newGeneration[q][i]][newGeneration[q][j+1]] - distances[newGeneration[q][i-1]][newGeneration[q][i]] - distances[newGeneration[q][i]][newGeneration[q][i+1]] - distances[newGeneration[q][j-1]][newGeneration[q][j]] - distances[newGeneration[q][j]][newGeneration[q][j+1]];
////                            std::cout << "\n " << i << "  " << j << "  cost: " << tmp2 << " = " << distances[newGeneration[q][i-1]][newGeneration[q][j]] << " + " << distances[newGeneration[q][j]][newGeneration[q][i+1]] << " + " << distances[newGeneration[q][j-1]][newGeneration[q][i]] << " + " << distances[newGeneration[q][i]][newGeneration[q][j+1]] << " - " << distances[newGeneration[q][i-1]][newGeneration[q][i]] << " - " << distances[newGeneration[q][i]][newGeneration[q][i+1]] << " - " << distances[newGeneration[q][j-1]][newGeneration[q][j]] << " - " << distances[newGeneration[q][j]][newGeneration[q][j+1]];
//                        }
//
//                        if(tmp2 < tmp){                                             //sprawdzenie czy wygenerowany sasiad jest lepszy od juz sprawdzonych
//                            k1 = i;
//                            k2 = j;
//                            tmp = tmp2;
//                        }
//                    }
//                }
//                if(tmp < 0)
//                {
//                    temp = newGeneration[q][k1];                               //zamiana najlepszych miast miejscami
//                    newGeneration[q][k1] = newGeneration[q][k2];
//                    newGeneration[q][k2] = temp;
////
////                    if(mmemetic == '1')
////                        std::cout << "\n zamieniono pozycje miasta na pozycji: " << k1 << " na pozycje " << k2 << " czyli miasta " << newGeneration[q][k2] << " na miasto " << newGeneration[q][k1] << " co pozwolilo nam zmodyfikowac dlugosc trasy o: " << tmp;
////                    if(mmemetic == '2')
////                        std::cout << "\n zamieniono miejscami miasta na pozycjach: " << k1 << " oraz " << k2 << " czyli miasta " << newGeneration[q][k2] << " oraz " << newGeneration[q][k1] << " co pozwolilo nam zmodyfikowac dlugosc trasy o: " << tmp;
////                    std::cout << "\n nowa sekwencja potomka nr: " << q << "    ";
////                    for(int i = 0; i <= cityamount; i++)
////                        std::cout << " " << newGeneration[q][i];
//                }
////                else
////                    std::cout << "\n nie warto przeprowadzac zadnych zmian.";
//            }
//        }

        switch(mmemetic){
            case '1':{  //insert

                for(int q = 0; q < popChild; q++){
                    tmp = INT_MAX; //Najmniejszy osiagniety przez nas wynik
                    std::cout << "\n stara sekwencja potomka nr: " << q << "    ";
                    for(int i = 0; i <= cityamount; i++)
                        std::cout << " " << newGeneration[q][i];

                    for(int i = 1; i < cityamount; i++){
                        for(int j = 1; j < cityamount; j++){
                            if(i < j)
                            {
//                                tmp2 = 0;       // wyliczanie roznicy w koszcie, obliczajac jedynie roznice miedzy sciezkami bedacymi czesciami zamienionych miast
                                tmp2 = distances[newGeneration[q][i-1]][newGeneration[q][j]] + distances[newGeneration[q][j]][newGeneration[q][i]] + distances[newGeneration[q][j-1]][newGeneration[q][j+1]] - distances[newGeneration[q][i-1]][newGeneration[q][i]] - distances[newGeneration[q][j-1]][newGeneration[q][j]] - distances[newGeneration[q][j]][newGeneration[q][j+1]];
                                std::cout << "\n " << i << "  " << j << "  cost: " << tmp2 << " = " << distances[newGeneration[q][i-1]][newGeneration[q][j]]  << " + " << distances[newGeneration[q][j]][newGeneration[q][i]] << " + " << distances[newGeneration[q][j-1]][newGeneration[q][j+1]] << " - " << distances[newGeneration[q][i-1]][newGeneration[q][i]] << " - " << distances[newGeneration[q][j-1]][newGeneration[q][j]] << " - " << distances[newGeneration[q][j]][newGeneration[q][j+1]];

                                if(tmp2 < tmp){         //sprawdzenie czy wygenerowany sasiad jest lepszy od juz sprawdzonych
                                    k1 = i;
                                    k2 = j;
                                    tmp = tmp2;
                                }
                            }
                            if(j < i)
                            {
//                                tmp2 = 0;       // wyliczanie roznicy w koszcie, obliczajac jedynie roznice miedzy sciezkami bedacymi czesciami zamienionych miast
                                tmp2 = distances[newGeneration[q][j-1]][newGeneration[q][j+1]] + distances[newGeneration[q][i]][newGeneration[q][j]] + distances[newGeneration[q][j]][newGeneration[q][i+1]] - distances[newGeneration[q][j-1]][newGeneration[q][j]] - distances[newGeneration[q][j]][newGeneration[q][j+1]] - distances[newGeneration[q][i]][newGeneration[q][i+1]];
                                std::cout << "\n " << i << "  " << j << "  cost: " << tmp2 << " = " << distances[newGeneration[q][j-1]][newGeneration[q][j+1]]  << " + " << distances[newGeneration[q][i]][newGeneration[q][j]] << " + " << distances[newGeneration[q][j]][newGeneration[q][i+1]] << " - " << distances[newGeneration[q][j-1]][newGeneration[q][j]] << " - " << distances[newGeneration[q][j]][newGeneration[q][j+1]] << " - " << distances[newGeneration[q][i]][newGeneration[q][i+1]];

                                if(tmp2 < tmp){         //sprawdzenie czy wygenerowany sasiad jest lepszy od juz sprawdzonych
                                    k1 = i;
                                    k2 = j;
                                    tmp = tmp2;
                                }
                            }
                        }
                    }
                    if(tmp < 0)
                    {
                        if(k1 < k2)
                        {
                            temp = newGeneration[q][k2];
                            for(int p = k2; p > k1; p--)
                                 newGeneration[q][p] = newGeneration[q][p-1];
                            newGeneration[q][k1] = temp;
                        }
                        if(k2 < k1)
                        {
                            temp = newGeneration[q][k2];
                            for(int p = k2; p < k1; p++)
                                 newGeneration[q][p] = newGeneration[q][p+1];
                            newGeneration[q][k2] = temp;
                        }


                        std::cout << "\n zamieniono pozycje miasta na pozycji: " << k1 << " na pozycje " << k2 << " czyli miasta " << newGeneration[q][k2] << " na miasto " << newGeneration[q][k1] << " co pozwolilo nam zmodyfikowac dlugosc trasy o: " << tmp;
                        std::cout << "\n nowa sekwencja potomka nr: " << q << "    ";
                        for(int i = 0; i <= cityamount; i++)
                            std::cout << " " << newGeneration[q][i];
                    }
                    else
                        std::cout << "\n nie warto przeprowadzac zadnych zmian.";
                }


                break;
            }
            case '2':{  //swap

                for(int q = 0; q < popChild; q++){
                    tmp = INT_MAX; //Najmniejszy osiagniety przez nas wynik
                    std::cout << "\n stara sekwencja potomka nr: " << q << "    ";
                    for(int i = 0; i <= cityamount; i++)
                        std::cout << " " << newGeneration[q][i];

                    for(int i = 1; i < cityamount-1; i++){
                        for(int j = i+1; j < cityamount; j++){

//                            tmp2 = 0;       // wyliczanie roznicy w koszcie, obliczajac jedynie roznice miedzy sciezkami bedacymi czesciami zamienionych miast
                            if(i + 1 == j){
                                tmp2 = distances[newGeneration[q][i-1]][newGeneration[q][j]] + distances[newGeneration[q][j]][newGeneration[q][i]] + distances[newGeneration[q][i]][newGeneration[q][j+1]] - distances[newGeneration[q][i-1]][newGeneration[q][i]] - distances[newGeneration[q][i]][newGeneration[q][j]] - distances[newGeneration[q][j]][newGeneration[q][j+1]];
                                std::cout << "\n " << i << "  " << j << "  cost: " << tmp2 << " = " << distances[newGeneration[q][i-1]][newGeneration[q][j]]  << " + " << distances[newGeneration[q][j]][newGeneration[q][i]] << " + " << distances[newGeneration[q][i]][newGeneration[q][j+1]] << " - " << distances[newGeneration[q][i-1]][newGeneration[q][i]] << " - " << distances[newGeneration[q][i]][newGeneration[q][j]] << " - " << distances[newGeneration[q][j]][newGeneration[q][j+1]];
                            }
                            else{
                                tmp2 = distances[newGeneration[q][i-1]][newGeneration[q][j]] + distances[newGeneration[q][j]][newGeneration[q][i+1]] + distances[newGeneration[q][j-1]][newGeneration[q][i]] + distances[newGeneration[q][i]][newGeneration[q][j+1]] - distances[newGeneration[q][i-1]][newGeneration[q][i]] - distances[newGeneration[q][i]][newGeneration[q][i+1]] - distances[newGeneration[q][j-1]][newGeneration[q][j]] - distances[newGeneration[q][j]][newGeneration[q][j+1]];
                                std::cout << "\n " << i << "  " << j << "  cost: " << tmp2 << " = " << distances[newGeneration[q][i-1]][newGeneration[q][j]] << " + " << distances[newGeneration[q][j]][newGeneration[q][i+1]] << " + " << distances[newGeneration[q][j-1]][newGeneration[q][i]] << " + " << distances[newGeneration[q][i]][newGeneration[q][j+1]] << " - " << distances[newGeneration[q][i-1]][newGeneration[q][i]] << " - " << distances[newGeneration[q][i]][newGeneration[q][i+1]] << " - " << distances[newGeneration[q][j-1]][newGeneration[q][j]] << " - " << distances[newGeneration[q][j]][newGeneration[q][j+1]];
                            }

                            if(tmp2 < tmp){                                             //sprawdzenie czy wygenerowany sasiad jest lepszy od juz sprawdzonych
                                k1 = i;
                                k2 = j;
                                tmp = tmp2;
                            }
                        }
                    }
                    if(tmp < 0)
                    {
                        temp = newGeneration[q][k1];                               //zamiana najlepszych miast miejscami
                        newGeneration[q][k1] = newGeneration[q][k2];
                        newGeneration[q][k2] = temp;

                        std::cout << "\n zamieniono miejscami miasta na pozycjach: " << k1 << " oraz " << k2 << " czyli miasta " << newGeneration[q][k2] << " oraz " << newGeneration[q][k1] << " co pozwolilo nam zmodyfikowac dlugosc trasy o: " << tmp;
                        std::cout << "\n nowa sekwencja potomka nr: " << q << "    ";
                        for(int i = 0; i <= cityamount; i++)
                            std::cout << " " << newGeneration[q][i];
                    }
                    else
                        std::cout << "\n nie warto przeprowadzac zadnych zmian.";
                }
                break;
            }
        }




        switch(mmutacji){
            case '1':{  //insert
                temp = 100;
                for(int i = 0; i < maxmutacji; i++)
                {
//                    std::cout << "\n dziecko 2: ";      //sprawdzenie
//                    for(int p = 0; p <= cityamount; p++)
//                        std::cout << " " << newGeneration[2][p];

                    for(int j = 0; j < popChild; j++)
                       if(rand() % temp <= wspmutacji)
                       {
                            k1 = rand() % (cityamount - 1) + 1;
                            do{
                                k2 = rand() % (cityamount - 1) + 1;
                            }while(k1 == k2);

                            if(k1 < k2){
                                tmp = k1;
                                k1 = k2;
                                k2 = tmp;
                            }

                            tmp = newGeneration[j][k2];  // (k1 > k2)
                            for(int z = k2; z < k1; z++)
                                newGeneration[j][z] = newGeneration[j][z + 1];
                            newGeneration[j][k1] = tmp;
                       }
                    temp = temp*1.5;
                }
                break;
            }
            case '2':{  //invert
                temp = 100;
                for(int i = 0; i < maxmutacji; i++)
                {
//                    std::cout << "\n dziecko 2: ";      //sprawdzenie
//                    for(int p = 0; p <= cityamount; p++)
//                        std::cout << " " << newGeneration[2][p];

                    for(int j = 0; j < popChild; j++)
                       if(rand() % temp <= wspmutacji)
                       {
                            k1 = rand() % (cityamount - 1) + 1;
                            do{
                                k2 = rand() % (cityamount - 1) + 1;
                            }while(k1 == k2);

                            if(k1 < k2){
                                tmp = k1;
                                k1 = k2;
                                k2 = tmp;
                            }

                            tmp2 = (k1 - k2)/2;     // (k1 > k2)

                            for(int z = 0; z <= tmp2; z++)
                            {
                                tmp = newGeneration[j][k2 + z];
                                newGeneration[j][k2 + z] = newGeneration[j][k1 - z];
                                newGeneration[j][k1 - z] = tmp;
                            }
                       }
                    temp = temp*1.5;
                }
                break;
            }
            case '3':{  //swap
                temp = 100;
                for(int i = 0; i < maxmutacji; i++)
                {
//                    std::cout << "\n dziecko 2: ";      //sprawdzenie
//                    for(int p = 0; p <= cityamount; p++)
//                        std::cout << " " << newGeneration[2][p];

                    for(int j = 0; j < popChild; j++)
                       if(rand() % temp <= wspmutacji)
                       {
                            k1 = rand() % (cityamount - 1) + 1;
                            do{
                                k2 = rand() % (cityamount - 1) + 1;
                            }while(k1 == k2);

                            tmp = newGeneration[j][k1];
                            newGeneration[j][k1] = newGeneration[j][k2];
                            newGeneration[j][k2] = tmp;

                       }
                    temp = temp*1.5;
                }
                break;
            }
            case '4':{  //skip mutation

                break;
            }
            default:{
                break;
            }
        }

//        for(int i = 0; i < popSize; i++){
//            for(int u = 0; u <= cityamount; u++)
//                std::cout << " " << oldGeneration[i][u];
//            std::cout << "  osobnik nr: " << i << "  droga: " << specimenValue[i] << "\n";}
//
//        for(int i = 0; i < popChild; i++){
//            for(int u = 0; u <= cityamount; u++)
//                std::cout << " " << newGeneration[i][u];
//            std::cout << "  osobnik nr: " << i << "  droga: " << childValue[i] << "\n";}


        for(int i = 0; i < popChild; i++){          //obliczanie drogi potomkow
            childValue[i] = 0;
            for(int j = 0; j < cityamount; j++)
                childValue[i] += distances[newGeneration[i][j]][newGeneration[i][j + 1]];
            if(childValue[i] < bestCost)
            {
                bestCost = childValue[i];
//                std::cout << "\n\n newbestpath: " << bestCost;
                for(int j = 0; j <= cityamount; j++)
                    bestPath[j] = newGeneration[i][j];
            }
//            std::cout << "\n\n dziecko " << i << " ma droge rowna " << childValue[i];
//
//            if(childValue[i] > 50000)
//                std::cout << "\n\n ZWARIOWALEM \n\n";
        }

//        for(int i = 0; i < popSize; i++){
//            for(int u = 0; u <= cityamount; u++)
//                std::cout << " " << oldGeneration[i][u];
//            std::cout << " - osobnik nr: " << i << "  droga: " << specimenValue[i] << "\n";}
//
//        for(int i = 0; i < popChild; i++){
//            for(int u = 0; u <= cityamount; u++)
//                std::cout << " " << newGeneration[i][u];
//            std::cout << " - dziecko nr: " << i << "  droga: " << childValue[i] << "\n";}

//        std::cout << "\n selekcja: " << iteration << "\n";



        if(sukcesja == true){   // w przypadku sukcesji ustawiamy wszystkich rodzicow w kolejce do nadpisania
            for(int i = 0; i < popSize; i++)
                bAllPop[i] = true;
            for(int i = 0; i < popChild; i++)
                bAllPop[i + popSize] = false;
        }
        else
            for(int j = 0; j < popSize + popChild; j++)    //zerowanie tablicy osobnikow do usuniecia
                bAllPop[j] = false;


        switch(mselekcji){
            case '1':{  //kola ruletki
//                allPaths = 0;
//                for(int j = 0; j < popSize + popChild; j++)    //zerowanie tablicy osobnikow do usuniecia
//                    bAllPop[j] = false;

                specimenMaxValue = INT_MAX;
                for(int i = 0; i < popSize; i++)            //znajdowanie najkrotszej sciezki w populacji
                    if(specimenValue[i] < specimenMaxValue)
                        specimenMaxValue = specimenValue[i];
                for(int i = 0; i < popChild; i++)
                    if(childValue[i] < specimenMaxValue)
                        specimenMaxValue = childValue[i];

//                std::cout << "\n\n mvaxalue " << specimenMaxValue;

//                for(int i = 0; i < popSize; i++)            //obliczanie szansy na rozmnozenie na podstawie wartosci o ktora jest osobnik gorszy od najlepszej sciezki
//                    allPaths += (specimenValue[i] - specimenMaxValue + 1);
//                for(int i = 0; i < popChild; i++)
//                    allPaths += (childValue[i] - specimenMaxValue + 1);

//                std::cout << "\n allpaths: " << allPaths <<"\n\n";

                for(int i = 0; i < (popChild - succession); i++){

                    allPaths = 0;
                    for(int i = 0; i < popSize; i++)            //obliczanie szansy na rozmnozenie na podstawie wartosci o ktora jest osobnik gorszy od najlepszej sciezki
                        if(bAllPop[i] == false)
                            allPaths += (specimenValue[i] - specimenMaxValue + 1);
                    for(int i = 0; i < popChild; i++)
                        if(bAllPop[popSize + i] == false)
                            allPaths += (childValue[i] - specimenMaxValue + 1);

//                std::cout << "\n allpaths: " << allPaths;
                                                            //stworzenie wartosci bedacej suma wszystkich mozliwych szans dla osobnikow na
                                                            // zostanie rodzicami (bycie lepszym od najgorszego o dana wartosc +1). nastepuje
                    tmp = rand() % allPaths;                // wylosowanie wartosci a nastepnie jest sprawdzane w ktorym osobniku znajduje sie wylosowana
                    tmp2 = 0;                               // szansa. Nastepnie jego wartosc jest odejmowana z puli i losuje sie jeszcze raz z jego pominieciem
//                    std::cout << "\n allpaths: " << allPaths;
//                    std::cout << " "<< tmp << "-";

                    for(int j = 0; j < popSize && tmp2 <= tmp; j++)
                    {                                       //sprawdzenie starej populacji, potem nowej
                        if(bAllPop[j] == false){
                            tmp2 += (specimenValue[j] - specimenMaxValue + 1);
                            if(tmp2 >= tmp){
                                bAllPop[j] = true;
//                                std::cout << "\n odejmowane oldgen: " << (specimenValue[j] - specimenMaxValue + 1);
//                                allPaths -= (specimenValue[j] - specimenMaxValue + 1);
//                                std::cout << "w " << i;
                            }
                        }
                    }
                    for(int j = 0; tmp2 < tmp; j++)
                    {
                        if(bAllPop[popSize + j] == false){
                            tmp2 += (childValue[j] - specimenMaxValue + 1);
                            if(tmp2 >= tmp){
                                bAllPop[popSize + j] = true;;
//                                std::cout << "\n odejmowane dziecka: " << (childValue[j] - specimenMaxValue + 1);
//                                allPaths -= (childValue[j] - specimenMaxValue + 1);
//                                std::cout << "v" << i;
                            }
                        }
                    }
                }
                break;
            }
            case '2':{  //ranking
                for(int i = succession; i < popSize + popChild; i++)
                    allPopOperator[i] = i;

//                std::cout << "\n";      //sprawdzenie
//                for(int i = 0; i < popChild + popSize; i++)
//                    std::cout << " " << allPopOperator[i];

                for(int i = (popSize + popChild - 1); i > succession; i--)
                {
                    for(int j = succession; j < i; j++)
                    {
                        if(allPopOperator[j] >= popSize){    //uwzglednianie 2 tabel
                            k1 = childValue[allPopOperator[j] - popSize];}
                        else{
                            k1 = specimenValue[allPopOperator[j]];}
                        if(allPopOperator[j + 1] >= popSize){
                            k2 = childValue[allPopOperator[j + 1] - popSize];}
                        else{
                            k2 = specimenValue[allPopOperator[j + 1]];}


                        if(k1 < k2)
                        {
                            tmp = allPopOperator[j];
                            allPopOperator[j] = allPopOperator[j + 1];
                            allPopOperator[j + 1] = tmp;
                        }


                    }
                }
//                std::cout << "\n";
//                for(int i = 0; i < popChild + popSize; i++)
//                    std::cout << " " << allPopOperator[i];
                for(int i = succession; i < popChild; i++)
                    bAllPop[allPopOperator[i]] = true;

                break;
            }
            case '3':{  //turniejowa
//                for(int j = 0; j < popSize + popChild; j++)    //zerowanie tablicy
//                    bAllPop[j] = false;

                for(int i = 0; i < popChild - succession; i++)
                {
                    for(int j = 0; j < popSize + popChild; j++)    //zerowanie tablicy
                        bAllPop2[j] = false;

                    temp = INT_MAX;             // to bedzie najgorsza znaleziona wartosc
                    for(int j = 0; j < wspselekcji; j++)
                    {
                        do{
                            tmp = rand() % (popSize + popChild);
                        }while(bAllPop2[tmp] == true || bAllPop[tmp] == true);
//                        std::cout << i << " wylosowalem: " << tmp << "  maxtemp: " << temp;
                        bAllPop2[tmp] = true;

                        if(tmp >= popSize){
//                            std::cout << " wiec sprawdzam rodzica nr: " << tmp << " o wartosci: " << childValue[tmp - popSize] <<"\n";
                            if(childValue[tmp - popSize] < temp){
                                temp = childValue[tmp - popSize];
                                tmp2 = tmp;}
                        }
                        else{
//                            std::cout << " wiec sprawdzam rodzica nr: " << tmp << " o wartosci: " << specimenValue[tmp] <<"\n";
                            if(specimenValue[tmp] < temp){
                                temp = specimenValue[tmp];
                                tmp2 = tmp;}
                        }
                    }
//                    std::cout << " do ballpop trafia nr: " << tmp2 << "\n";
                    bAllPop[tmp2] = true;
                }
                temp = 0;
                for(int i = 0; i < popChild + popSize; i++){
//                    std::cout << " " << bAllPop[i];
                    if(bAllPop[i] == true) temp++;}
                if(temp != popChild)
//                    std::cout << "\n\n\n\n POPSULEM TURNIEJ!!! \n temp: " << temp << "\n\n\n\n";
                break;
            }
//            case '4':{  //rangowa
//
//                break;
//            }
        }

//        std::cout << "\n";
//        for(int t = 0; t < popSize + popChild; t++)
//            std::cout << " " << bAllPop[t];

        tmp = 0;
        for(int i = 0; i < popChild; i++)       //nadpisywanie wylonionych oldGen nowymi osobnikami
        {
//            std::cout << "\n  -potomek: ";
//            for(int u = 0; u <= cityamount; u++)
//                std::cout << " " << newGeneration[i][u];
            if(bAllPop[popSize + i] == false){           //dany potomek nie zostal przeznaczony do usuniecia, trzeba go przeniesc
                while(childValue[i] != 0)
                {
//                    std::cout << "\n  -rodzic: ";
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << oldGeneration[tmp][u];
                    if(bAllPop[tmp] == true)
                    {
                        for(int u = 0; u <= cityamount; u++)
                        {
                            oldGeneration[tmp][u] = newGeneration[i][u];
                            newGeneration[i][u] = 0;
                        }
//                        std::cout << "\n zamieniam " << specimenValue[tmp] << " na " << childValue[i];
                        specimenValue[tmp] = childValue[i];
                        childValue[i] = 0;
                        bAllPop[tmp] = false;
//                        std::cout << " z takim rezultatem: " << specimenValue[tmp] << " oraz zeruje " << childValue[i] << " nr przejscia: " << i;
                    }
                    tmp++;
//                    std::cout << " ." << childValue[i];
                }
            }
            else
            {
                for(int j = 0; j <= cityamount; j++)
                    newGeneration[i][j] = 0;
                childValue[i] = 0;
//                std::cout << "\n usuwam dzieciaka nr: " << i;
            }
        }
        for(int i = 0; i < popSize + popChild; i++)
            bAllPop[i] = false;
//
//        std::cout << "\n przenioslem wszystko ";
//        std::cout << "\n stara generacja potomkow: ";
//        for(int i = 0; i < popChild; i++)
//        for(int j = 0; j <= cityamount; j++)
//            std::cout << " " << newGeneration[i][j];

//                    std::cout << "\n\n wykonane\n nowa generacja:\n";
//                    for(int i = 0; i < popSize; i++){
//                        std::cout << "\n droga: " << specimenValue[i] << "  sciezka: ";
//                        for(int u = 0; u <= cityamount; u++)
//                            std::cout << " " << oldGeneration[i][u];
//                    }


        end = clock();

        if((kstopu == '1' && double(end - begin) / CLOCKS_PER_SEC > ttime) || (kstopu == '3' && double(end - begin) / CLOCKS_PER_SEC > ttime))
            {keepGoing = false;
            std::cout << "\n warunek czasu, wykonywano przez: " << iteration << " iteracji";
            }
        if((kstopu == '2' && iteration >= maxiteration) || (kstopu == '3' && iteration >= maxiteration))
            {keepGoing = false;
            std::cout << "\n warunek iteracji, iteracja nr: " << iteration;
            }
    }
    while(keepGoing);

//            for(int y = 0; y < popSize; y++){
//                std::cout << "\n";
//                for(int u = 0; u <= cityamount; u++)
//                    std::cout << " " << newGeneration[y][u];}

    std::cout<<"\n\n\nCzas wykonania proby: " << double(end - begin) / CLOCKS_PER_SEC;
    std::cout<<"\nNajlepszy wynik proby: " << bestCost << "\nNajlepsza sciezka: ";
    for(int i = 0; i <= cityamount; i++)
        std::cout << " " << bestPath[i];

    delete[] bCity;
    delete[] bAllPop;
    delete[] bAllPop2;
//    delete[] bPopSize;
//    delete[] bPopChild;
    for(int i = 0; i < popSize; i++)        // zwolnij pamiec
        delete[] oldGeneration[i];
    for(int i = 0; i < popChild; i++)
        delete[] newGeneration[i];
    delete[] oldGeneration;
    delete[] newGeneration;
    delete[] specimenValue;
    delete[] childValue;
    delete[] newParents[0];
    delete[] newParents[1];
    delete[] cityOperator;
    delete[] allPopOperator;
    delete[] bestPath;

    return bestCost;
}


int mrowki() //QAS
{
    double feromon = 0.0;
    for(int i = 0; i < cityamount; i++){
        for(int j = 0; j < cityamount; j++){
            if(i != j){
                feromon += distances[i][j];
            }
        }
    }
    feromon = feromon / ((cityamount - 1) * (cityamount - 1));
//    std::cout << "\n startowy feromon: " << feromon << "\n";

    int bestCost = INT_MAX;
    int* bestPath = new int[cityamount + 1];
    double evap = 0.5; // stopien parowania feromonu, zakres <0,1>
    double alfa = 1; // stopien atrakcyjnosci feromonu
    double beta = 3; // stopien atrakcyjnosci krotszej sciezki
    int colonySize = cityamount; // wielkosc koloni
    int maxIteration = 100;  //ilosc iteracji programu


    char choice;
    int tmp = 0;
    int tmp2 = 0;
    int tmpLos = 0;
    int tmp3 = 0;
    double tmpMax = 0.0;
    int x = 0;
    double temp = 0.0;
    double tempD = 0.0;
    double temp2 = 0.0;
    int rzad = 0;

    std::cout << "\n\n Algorytm mrowkowy:\n Czy chcesz wprowadzic wlasne parametry? (y. = tak): ";
    choice = getche();
    if(choice == 'y')
    {
        std::cout << "Podaj stopien parowania feromonu (zakres 0-1): ";
        std::cin >> evap;
        std::cout << "Podaj parametr alfa: ";
        std::cin >> alfa;
        std::cout << "Podaj parametr beta: ";
        std::cin >> beta;
        std::cout << "Podaj wielkosc koloni: ";
        std::cin >> colonySize;
        std::cout << "Podaj ilosc iteracji: ";
        std::cin >> colonySize;
    }

    bool** antTabu = new bool*[colonySize];
    int** antPath = new int*[colonySize];
    int* distanceToTravel = new int[colonySize];
    for(int i = 0; i < colonySize; i++){
        antTabu[i] = new bool[cityamount];
        antPath[i] = new int[cityamount + 1];
        distanceToTravel[i] = 0;
        tmp = rand() % cityamount;
        antPath[i][0] = antPath[i][cityamount] = tmp;
        for(int j = 0; j < cityamount; j++){
            antTabu[i][j] = false;}
        antTabu[i][tmp] = true;
    }

    double** phTab = new double*[cityamount];   // tablica feromonu
    for(int i = 0; i < cityamount; i++){
        phTab[i] = new double[cityamount];
        for(int j = 0; j < cityamount; j++)
            phTab[i][j] = feromon;                    // poczatkowa ilosc feromonu na kazdej krawedzi
    }

//    bool* greedyBool = new bool[cityamount];
//    for(int i = 0; i < cityamount; i++)
//        greedyBool[i] = false;
//    greedyBool[0] = true;
//
//
//    bestPath[0] = bestPath[cityamount] = 0;
//    for(int i = 0; i < cityamount; i++)        //GreedyAlgoritm
//    {
//        tmp = INT_MAX
//        tmp2 = 0;
//        for(int j = 0; j < cityamount; j++)
//        {
//            if(distances[bestPath[i]][j] < tmp)
//                tmp = distances[bestPath[i]][j];
//                j = tmp2;
//        }
//
//    }


    for(int q = 0; q < maxIteration; q++)
    {
        for(int i = 0; i < (cityamount - 1); i++) // i - pozycja w sekwencji miast ktora jest aktualnie opracowywana
        {
            if(i == (cityamount - 2))
            {
                for(int j = 0; j < colonySize; j++){
                    for(int k = 0; k < cityamount; k++)
                    {
                        if(antTabu[j][k] == false && k != antPath[j][cityamount])
                            antPath[j][i + 1] = k;
                    }
                }
            }
            else
            {
                for(int j = 0; j < colonySize; j++) // j - nr aktualnie opracowywanej mrowki
                {
                    tmpMax = 0.0;     //to bedzie caly przedzial losowania
                    temp2 = 0.0;
                    for(int k = 0; k < cityamount; k++) //wyliczanie wszystkich przejsc do nastepnych miast
                    {
                        if(antTabu[j][k] == false){
                            tmpMax += pow(phTab[j][k], alfa) / pow( distances[antPath[j][i]][k], beta);}
                    }
    //                std::cout << "\n tmpMax: " << tmpMax ;
                    for(rzad = 0; tmpMax < 10000; rzad++) // sprawdzanie rzedu wielkosci, niezbedne do losowania
                        tmpMax = tmpMax * 10;
    //                std::cout << " rzad: " << rzad << " nowe tmpMax: " << tmpMax;

                    tmp3 = tmpMax;
                    tmpLos = rand() % tmp3;     //losujemy miasto z okreslonym prawdopodobienstwem
    //                std::cout << " tmp los:  " << tmpLos << "\n";

                    tmp2 = 0;
                    x = 0;

                    do{
                        if(antTabu[j][x] == false){
                            temp = pow(phTab[j][x], alfa) / pow(distances[antPath[j][i]][x], beta);
                            temp2 += temp * pow(10, rzad);
                            tmp2 = temp2;
                        }
                        x++;
    //                    std::cout << "   " << temp2;
                    }while(tmp2 < tmpLos);
                    antTabu[j][x - 1] = true;
                    antPath[j][i + 1] = x - 1;

    //                std::cout << "\n mrowka: " << j << " wykonuje przejscie z: " << antPath[j][i] << " do: " << antPath[j][i + 1] << " pokonujac przy tym: " << distances[antPath[j][i]][antPath[j][i + 1]] << " nowy vBool: \n";
    //                for(int o = 0; o < cityamount; o++)
    //                    std::cout << " " << antTabu[j][o];

                }
            }
//            std::cout << "\n\n nowa fala";

            for(int j = 0; j < cityamount; j++)   //pomnozenie ilosci feromonu na sciezkach przez evap
                for(int k = 0; k < cityamount; k++)
                    phTab[j][k] *= evap;


            for(int j = 0; j < colonySize; j++){ // j - nr aktualnie opracowywanej mrowki
                tempD = feromon / distances[antPath[j][i]][antPath[j][i + 1]];
//                std::cout << "\n do: " << phTab[antPath[j][i]][antPath[j][i + 1]] << " tempD: " << feromon << " / " << distances[antPath[j][i]][antPath[j][i + 1]] << " wiec dodajemy " << (feromon * tempD);
                phTab[antPath[j][i]][antPath[j][i + 1]] += (feromon * tempD); //dodawanie feromonu tam gdzie bylo przejscie: feromon * (feromon/distances[][])
            }

//            std::cout << "\n sprawdzenie: ";
//            for(int j = 0; j < cityamount; j++){  // sprawdzanie
//                for(int k = 0; k < cityamount; k++)
//                    if(phTab[j][k] != phTab[0][0])
//                        std::cout << "\n Dla mrowki: " << j << " na pozycji " << k << " nowy feromon wynosi: " << phTab[j][k];
//            }

        }

        for(int j = 0; j < cityamount; j++)   //pomnozenie ilosci feromonu na sciezkach przez evap po raz ostatni
            for(int k = 0; k < cityamount; k++)
                phTab[j][k] *= evap;

        for(int j = 0; j < colonySize; j++) // j - nr aktualnie opracowywanej mrowki
            phTab[antPath[j][cityamount - 1]][antPath[j][cityamount]] += (feromon * (feromon / distances[antPath[j][cityamount - 1]][antPath[j][cityamount]])); //dodawanie feromonu tam gdzie bylo przejscie: feromon * (feromon/distances[][])



        //obliczanie drogi i zerowanie tabu oraz znajdowanie bestpath i bestcost

        for(int j = 0; j < colonySize; j++){    //nr mrowki / liczenie kosztu sekwencji
            tmp = 0;
            for(int k = 0; k < cityamount; k++){    //nr miasta w seq
                tmp += distances[antPath[j][k]][antPath[j][k + 1]];
            }

//            std::cout << "\n zkoszt: " << tmp << " seq: ";  // wypisywanie wynikow
//            for(int k = 0; k <= cityamount; k++)
//                std::cout << " " << antPath[j][k];

            if(tmp < bestCost){
                bestCost = tmp;
                for(int k = 0; k <= cityamount; k++)
                    bestPath[k] = antPath[j][k];
            }
            if(tmp > 100000)
            {
                std::cout << "\n\npopsute\n\n";
                for(int k = 0; k < cityamount; k++)
                    std::cout << " " << antTabu[j][k];
            }



        }

        for(int j = 0; j < colonySize; j++)
            for(int k = 0; k < cityamount; k++)
                antTabu[j][k] = false;

        std::cout << "\n iteracja nr" << q << " zakonczona!  Aktualny bestCost = " << bestCost;
    }

    std::cout << "\n\n Najlepszy znaleziony wynik: " << bestCost << " zostal otrzymany jako wynik sekwencji: \n";
    for(int i = 0; i <= cityamount; i++)
        std::cout << " " << bestPath[i];


    for(int i = 0; i < colonySize; i++){    // sekcja czyszczenia pamięci
        delete[] antTabu[i];
        delete[] antPath[i];
    }
    for(int i = 0; i < cityamount; i++)
        delete[] phTab[i];
    delete[] phTab;
    delete[] distanceToTravel;
    delete[] antTabu;
    delete[] antPath;
    delete[] bestPath;

    return bestCost;
}
