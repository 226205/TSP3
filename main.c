// Dodatkowe rzeczy:
//- pierwsze 1/3 sekwencji miast jest generowana losowo, reszta za pomocą Greedy
//- 2 metody selekcji rodzicow
//- 3 metody krzyzowania
//- 4 metody mutacji
//- 3 metody selekcji osobnikow

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
int genetical(int, int, int, int, int, char, char, char, char, int, int);


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
    int maxiteration = 100;
    int ttime = 4;
    int popSize = 60;
    int popChild = 20;
    char mkrzyzowania = '2';
    char mmutacji = '3';
    char mselekcji = '1';
    char mrodzica = '1';
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
        if(mkrzyzowania == '3') std::cout << "\n Metoda krzyzowania: HX";
        std::cout << "\n Wspolczynnik krzyzowania: " << wspkrzyzowania;
        if(mmutacji == '1') std::cout << "\n Metoda mutacji: insert";
        if(mmutacji == '2') std::cout << "\n Metoda mutacji: invert";
        if(mmutacji == '3') std::cout << "\n Metoda mutacji: swap";
        std::cout << "\n Wspolczynnik mutacji: " << wspmutacji;
        if(mselekcji == '1') std::cout << "\n Metoda selekcji osobnikow: kola ruletki";
        if(mselekcji == '2') std::cout << "\n Metoda selekcji osobnikow: rankingowa";
        if(mselekcji == '3') std::cout << "\n Metoda selekcji osobnikow: turniejowa";
        if(mrodzica == '1') std::cout << "\n Metoda selekcji rodzicow: kola ruletki";
        if(mrodzica == '2') std::cout << "\n Metoda selekcji rodzicow: losowa";
        std::cout << "\n Wielkosc populacji: " << popSize;
        std::cout << "\n Ilosc potomkow w kazdym pokoleniu populacji: " << popChild;

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
                std::cout << "\n\n Wybierz metode krzyzowania z ponizszych: ";
                std::cout << "\n 1. OX";
                std::cout << "\n 2. PMX";
                std::cout << "\n 3. HX";
                std::cout << "\n Twoj wybor: ";
                mkrzyzowania = getche();
                if(mkrzyzowania != '1' && mkrzyzowania != '2' && mkrzyzowania != '3') std::cout << "\n Nie ma takiej metody! Sprobuj ponownie!";
            } while (mkrzyzowania != '1' && mkrzyzowania != '2' && mkrzyzowania != '3');
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
                std::cout << "\n\n Wybierz metode mutacji z ponizszych: ";
                std::cout << "\n 1. insert";
                std::cout << "\n 2. invert";
                std::cout << "\n 3. swap";
                std::cout << "\n Twoj wybor: ";
                mmutacji = getche();
                if(mmutacji != '1' && mmutacji != '2' && mmutacji != '3') std::cout << "\n Nie ma takiej metody! Sprobuj ponownie!";
            } while (mmutacji != '1' && mmutacji != '2' && mmutacji != '3');
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
                std::cout << "\n\n Wybierz metode selekcji osobnikow z ponizszych: ";
                std::cout << "\n 1. kola ruletki";
                std::cout << "\n 2. rankingowa";
                std::cout << "\n 3. turniejowa";
                std::cout << "\n Twoj wybor: ";
                mselekcji = getche();
                if(mselekcji != '1' && mselekcji != '2' && mselekcji != '3') std::cout << "\n Nie ma takiej metody! Sprobuj ponownie!";
            } while (mselekcji != '1' && mselekcji != '2' && mselekcji != '3');
            break;
        }
        case '7':
        {
            do {
                std::cout << "\n\n Wybierz metode selekcji rodzicow z ponizszych: ";
                std::cout << "\n 1. kola ruletki";
                std::cout << "\n 2. losowa";
//                std::cout << "\n 3. turniejowa";
                std::cout << "\n Twoj wybor: ";
                mrodzica = getche();
                if(mrodzica != '1' && mrodzica != '2'/* && mrodzica != '3'*/) std::cout << "\n Nie ma takiej metody! Sprobuj ponownie!";
            } while (mrodzica != '1' && mrodzica != '2'/* && mrodzica != '3'*/);
            break;
        }
        case '8':
        {
            do {
                std::cout << "\n\n Podaj wielkosc populacji (zakres testowy: 10 - 500): ";
                std::cin >> popSize;
                if(popSize < 10 || popSize > 500) std::cout << "\n Wielkosc nie miesci sie w zakresie! Sprobuj ponownie!";
            } while (popSize < 10 || popSize > 500);
            do {
                std::cout << "\n\n Podaj ilosc potomkow na pokolenie (zakres: 1 - " << popSize <<"): ";
                std::cin >> popChild;
                if(popChild < 1 || popChild > popSize) std::cout << "\n Wielkosc nie miesci sie w zakresie! Sprobuj ponownie!";
            } while (popChild < 1 || popChild > popSize);
            break;
        }
        case '9':
        {
            std::cout << "\n\n " << genetical(kstopu, maxiteration, ttime, popSize, popChild, mkrzyzowania, mmutacji, mselekcji, mrodzica, wspkrzyzowania, wspmutacji);
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
                std::cout << "\n\n " << genetical(kstopu, maxiteration, ttime, popSize, popChild, mkrzyzowania, mmutacji, mselekcji, mrodzica, wspkrzyzowania, wspmutacji);
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

int genetical(int kstopu, int maxiteration, int ttime, int popSize, int popChild, char mkrzyzowania, char mmutacji, char mselekcji, char mrodzica, int wspkrzyzowania, int wspmutacji)
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

    int bestCost = INT_MAX;
    int iteration = 0;
    bool keepGoing = true;
    clock_t begin = clock();
    std::clock_t end = clock();
    int specimenMaxValue = 0;

    int amountOfRandom = std::max(cityamount / 3, 3);
    int tempR, tempV, temp, fA, tA, allPaths, tmp, tmp2, k1, k2, x;
//    std::cout << "\n\n" << amountOfRandom << "\n\n";
    int* pOperator = new int[cityamount + 1];
    int* bestPath = new int[cityamount + 1];
    int* specimenValue = new int[popSize];
    for(int i = 0; i < popSize; i++)
        specimenValue[i] = 0;

    bool* visited = new bool[cityamount + 1];            //stworzenie tablicy mowiacej czy dana liczba juz wystapila w sekwencji
    visited[0] = visited[cityamount] = true;              //podpisanie pierwszego i ostatniego elementu jako juz wykonanego
    pOperator[0] = pOperator[cityamount] = 0;

    int** newGeneration = new int* [popChild];               // dwuwymiarowa tablica dynamiczna okreslajaca sciezki osobnikow przyszlej generacji
    int* childValue = new int[popChild];
    int** newParents = new int* [popChild];
    for(int i = 0; i < popChild; ++i)
    {
        newParents[i] = new int[2];
        childValue[i] = 0;
        newGeneration[i] = new int[cityamount + 1];
        for(int j = 0; j <= cityamount; j++)
            newGeneration[i][j] = 0;
    }

    int** oldGeneration = new int* [popSize];               // dwuwymiarowa tablica dynamiczna okreslajaca sciezki osobnikow juz obecnej generacji
    for(int i = 0; i < popSize; ++i)
    {
        oldGeneration[i] = new int[cityamount + 1];
        oldGeneration[i][0] = oldGeneration[i][cityamount] = 0;     //ustawienie pierwszego miasta jako poczatkowego i koncowego

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
            oldGeneration[i][j] = tempR + tA;
//            specimenValue[i] += distances[oldGeneration[i][j-1]][oldGeneration[i][j]];
        }
        for(int j = amountOfRandom; j < cityamount; j++)        //GreedyAlgoritm
        {
            tempV = INT_MAX;
            for(int p = 1; p < cityamount; p++)
                if(visited[p] == false && distances[oldGeneration[i][j-1]][p] < tempV){
                    tempV = distances[oldGeneration[i][j-1]][p];
                    temp = p;
                }
            visited[temp] = true;
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

        std::cout << "\n switch: " << iteration;
        switch(mrodzica){

            case '1':{  //kola ruletki
                allPaths = 0;

                for(int i = 0; i < popSize; i++)            //znajdowanie najdluzszej sciezki w populacji
                    if(specimenValue[i] > specimenMaxValue)
                        specimenMaxValue = specimenValue[i];
//                std::cout << "\n sMax: " << specimenMaxValue;

                for(int i = 0; i < popSize; i++)            //obliczanie szansy na rozmnozenie na podstawie wartosci o ktora jest osobnik lepszy od najgorszej sciezki
                    allPaths += (specimenMaxValue - specimenValue[i] + 1);

                std::cout << "\n maxVal: " << specimenMaxValue << "  allpaths: " << allPaths;

                x = 0;
                temp = -1;

                for(int i = 0; i < popChild; i++){

                    x = 0;
                    temp = -1;
                                                                // stworzenie wartosci bedacej suma wszystkich mozliwych szans dla osobnikow na
                    do{                                         // zostanie rodzicami (bycie lepszym od najgorszego o dana wartosc +1). nastepuje
                        tmp = rand() % allPaths;                // wylosowanie wartosci a nastepnie jest sprawdzane w ktorym osobniku znajduje sie wylosowana
                        tmp2 = 0;                               // szansa. Nastepnie jego wartosc jest odejmowana z puli i losuje sie jeszcze raz z jego pominieciem
                        for(int j = 0; tmp2 < tmp; j++)
                        {
                            tmp2 += (specimenMaxValue - specimenValue[j] + 1);
                            if(tmp2 >= tmp){
                                newParents[i][x] = j;
                                std::cout << "\n tmp: " << tmp << " tmp2: " << tmp2 << " maxrand: " << allPaths << " specimenMaxValue: " << specimenMaxValue << " specimenValue[j]: "  << specimenValue[j];
                            }
                        }
                        if(tmp2 > tmp + 10000){     //sprawdzenie
                            std::cout << "\n";
                            for(int w = 0; w <= cityamount; w++)
                                std::cout << " " << oldGeneration[i][w];
                            std::cout << " value: " << specimenValue;
                        }
                        x = 1;
                        temp++;
                    }while(newParents[i][0] == newParents[i][1] || temp == 0);


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
                        std::cout << "\n\n POPSULEM \n\n";
                }
//                for(int i = 0; i< popChild; i++)
//                    std::cout << "\n parent: " << newParents[i][0] << " " << newParents[i][1];
                break;
            }
            case '2':{  //losowa
                for(int i = 0; i < popChild; i++)
                {
                    newParents[i][0] = rand() % popSize;
                    newParents[i][1] = rand() % (popSize - 1);
                    if(newParents[i][0] <= newParents[i][1])
                        newParents[i][1]++;

                    if(newParents[i][1] >= popSize || newParents[i][0] >= popSize)
                        std::cout << "\n\n\n\n\n\n POPSULEM \n\n\n\n\n\n";

                }
//                for(int i = 0; i< popChild; i++)
//                    std::cout << "\n parent: " << newParents[i][0] << " " << newParents[i][1];
                break;
            }
//            case '3':{  //
//
//                break;
//            }
        }
        std::cout << "\n krzyzowanie: " << iteration;
        switch(mkrzyzowania){
            case '1':{  //OX

                break;
            }
            case '2':{  //PMX
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

                for(int i = 0; i < popChild; i++)
                {
                    k1 = rand() % (cityamount - 1) + 1;
                    k2 = rand() % (cityamount - 1) + 1;
                    if(k1 > k2){
                        temp = k1;
                        k1 = k2;
                        k2 = temp;
                    }
                    for(int j = 1; j < cityamount; j++){
                        visited[j] = false;
                        pOperator[j] = 0;
                    }
                    for(int j = k1; j <= k2; j++){
                        newGeneration[i][j] = oldGeneration[newParents[i][0]][j];
                        visited[oldGeneration[newParents[i][0]][j]] = true;
                    }

                    tmp = 0;
//                    std::cout << "\nt3: " << tmp << "   rodzic: " << newParents[i][1] << "\n";
                    for(int j = k1; j <= k2; j++){      //sprawdzamy te same co przeniesione tylko z p2
//                        std::cout << "." << j;
                        tempV = oldGeneration[newParents[i][1]][j];
//                        std::cout << "p";
                        if(visited[tempV] == false){     //sprawdzenie ktore z wierzcholkow rodzica2 z tego przedzialu nie zostaly uzyte przy krzyzowaniu do potomka
//                            std::cout << "k";
                            pOperator[j] = oldGeneration[newParents[i][1]][j];
                            tmp++;
                        }
                    }

//                    std::cout << "\n\n WEJSCIOWY TMP: " << tmp << "\n\n";
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << newGeneration[i][u];
//                    std::cout << "  - odwedzone miasta w potomku\n";
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << pOperator[u];
//                    std::cout << "  - pOperator\n\n";

//                    std::cout << "\n tmp: " << tmp << " iteracja i: " << i;
                    tmp2 = 1;
                    while(tmp > 0)
                    {   /*std::cout << "PMX4";*/
                        if(pOperator[tmp2] != 0)
                            for(int j = 1; j < cityamount; j++)
                                if(oldGeneration[newParents[i][0]][tmp2] == oldGeneration[newParents[i][1]][j] && pOperator[j] == 0)
                                {
//                                    std::cout <<" j: " << j;
                                    pOperator[j] = pOperator[tmp2];
                                    pOperator[tmp2] = 0;
                                    if(newGeneration[i][j] == 0)
                                    {
//                                        std::cout <<"\n WSZEDLEM222!";
                                        newGeneration[i][j] = pOperator[j];
                                        tmp--;
                                        pOperator[j] = 0;
                                    }
                                }
//                        std::cout << " tmp: " << tmp << "  tmp2: " << tmp2 << "  pOperator: " << pOperator[tmp2] << "\n";
                        tmp2++;
                        if(tmp2 == cityamount)
                            tmp2 = 1;
                    }

//                    std::cout << "\n\n KONIECPMX\n\n";

//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << newGeneration[i][u];
//                    std::cout << "  -potomek1\n";

                    for(int j = 1; j < cityamount; j++)         //dopisanie pozostalych sciezek
                        if(newGeneration[i][j] == 0)
                            newGeneration[i][j] = oldGeneration[newParents[i][1]][j];

//                std::cout << "\n\n k1: " << k1 << "  k2: " << k2 << "\n";
//                for(int u = 0; u <= cityamount; u++)
//                    std::cout << " " << oldGeneration[newParents[i][0]][u];
//                    std::cout << "  -rodzic1\n";
//                for(int u = 0; u <= cityamount; u++)
//                    std::cout << " " << oldGeneration[newParents[i][1]][u];
//                    std::cout << "  -rodzic2\n";
//                for(int u = 0; u <= cityamount; u++)
//                    std::cout << " " << newGeneration[i][u];
//                    std::cout << "  -potomek2\n";
//                for(int u = 0; u <= cityamount; u++)
//                    std::cout << " " << visited[u];
//                    std::cout << "  -odwedzone miasta\n";
//                for(int u = 0; u <= cityamount; u++)
//                    std::cout << " " << pOperator[u];

                }
                std::cout << "\nkrzyzowaniewyjsciepmx: " << iteration;
                break;
            }
            case '3':{  //HX


                break;
            }
        }

        switch(mmutacji){
            case '1':{  //insert

                break;
            }
            case '2':{  //invert

                break;
            }
            case '3':{  //swap

                break;
            }
            case '4':{  //scramble

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
//            std::cout << "  osobnik nr: " << i << "  droga: " << specimenValue[i] << "\n";}
//
//        for(int i = 0; i < popChild; i++){
//            for(int u = 0; u <= cityamount; u++)
//                std::cout << " " << newGeneration[i][u];
//            std::cout << "  osobnik nr: " << i << "  droga: " << childValue[i] << "\n";}

        std::cout << "\n selekcja: " << iteration;

        switch(mselekcji){
            case '1':{  //kola ruletki
                allPaths = 0;

                for(int i = 0; i < popSize; i++)            //znajdowanie najkrotszej sciezki w populacji
                    if(specimenValue[i] < specimenMaxValue)
                        specimenMaxValue = specimenValue[i];
                for(int i = 0; i < popChild; i++)
                    if(childValue[i] < specimenMaxValue)
                        specimenMaxValue = childValue[i];

//                std::cout << "\n\n mvalue" << specimenMaxValue;

                for(int i = 0; i < popSize; i++)            //obliczanie szansy na rozmnozenie na podstawie wartosci o ktora jest osobnik gorszy od najlepszej sciezki
                    allPaths += (specimenValue[i] - specimenMaxValue + 1);
                for(int i = 0; i < popChild; i++)
                    allPaths += (childValue[i] - specimenMaxValue + 1);

//                std::cout << "\n\n allpaths" << allPaths;

                for(int i = 0; i < popChild; i++){           //stworzenie wartosci bedacej suma wszystkich mozliwych szans dla osobnikow na
                                                            // zostanie rodzicami (bycie lepszym od najgorszego o dana wartosc +1). nastepuje
                    tmp = rand() % allPaths;                // wylosowanie wartosci a nastepnie jest sprawdzane w ktorym osobniku znajduje sie wylosowana
                    tmp2 = 0;                               // szansa. Nastepnie jego wartosc jest odejmowana z puli i losuje sie jeszcze raz z jego pominieciem
//                    std::cout << "\n allpaths: " << allPaths;
                    for(int j = 0; j < popSize && tmp2 < tmp; j++)
                    {                                    //sprawdzenie starej populacji, potem nowej
                        if(oldGeneration[j][0] != -1){      // w wypadku odrzucania osobnika ustawiamy jego pole startowe na -1
                            tmp2 += (specimenValue[j] - specimenMaxValue + 1);
                            if(tmp2 >= tmp){
                                oldGeneration[j][0] = -1;
//                                std::cout << "\n odejmowane oldgen: " << (specimenValue[j] - specimenMaxValue + 1);
                                allPaths -= (specimenValue[j] - specimenMaxValue + 1);
//                                std::cout << "\n allpaths: " << allPaths;
                            }
                        }
                    }
                    for(int j = 0; tmp2 < tmp; j++)
                    {
                        if(newGeneration[j][0] != -1){
                            tmp2 += (childValue[j] - specimenMaxValue + 1);
                            if(tmp2 >= tmp){
                                newGeneration[j][0] = -1;
//                                std::cout << "\n odejmowane dziecka: " << (childValue[j] - specimenMaxValue + 1);
                                allPaths -= (childValue[j] - specimenMaxValue + 1);
//                                std::cout << "\n allpaths: " << allPaths;
                            }
                        }
                    }
                }
                break;
            }
            case '2':{  //ranking

                break;
            }
            case '3':{  //turniejowa

                break;
            }
        }

//        std::cout << "\n\n check out";

        tmp = 0;
        for(int i = 0; i < popChild; i++)       //nadpisywanie wylosowanych oldGen nowymi osobnikami
        {
//            std::cout << "\n  -potomek: ";
//            for(int u = 0; u <= cityamount; u++)
//                std::cout << " " << newGeneration[i][u];
            std::cout << " ide sprawdzic " << i;
            if(newGeneration[i][0] == 0){
                std::cout << " zw";
                while(childValue[i] != 0)
                {
//                    std::cout << "\n  -rodzic: ";
//                    for(int u = 0; u <= cityamount; u++)
//                        std::cout << " " << oldGeneration[tmp][u];
                    std::cout << " w: " << oldGeneration[tmp][0];
                    if(oldGeneration[tmp][0] == -1)
                    {
                        for(int u = 0; u <= cityamount; u++)
                        {
                            oldGeneration[tmp][u] = newGeneration[i][u];
                            newGeneration[i][u] = 0;
                        }
                        std::cout << "\n zamieniam " << specimenValue[tmp] << " na " << childValue[i];
                        specimenValue[tmp] = childValue[i];
                        childValue[i] = 0;
                        std::cout << " z takim rezultatem: " << specimenValue[tmp] << " oraz zeruje " << childValue[i] << " nr przejscia: " << i;
                    }
                    tmp++;
                    std::cout << " ." << childValue[i];
                }
            }
            else
            {
                for(int j = 0; j <= cityamount; j++)
                    newGeneration[i][j] = 0;
                childValue[i] = 0;
                std::cout << "\n usuwam dzieciaka nr: " << i;
            }
        }
        std::cout << "\n przenioslem wszystko";

//                    std::cout << "\n\n wykonane\n nowa generacja:\n";
//                    for(int i = 0; i < popSize; i++){
//                        std::cout << "\n droga: " << specimenValue[i] << "  sciezka: ";
//                        for(int u = 0; u <= cityamount; u++)
//                            std::cout << " " << oldGeneration[i][u];
//                    }

//przenies nowa gen na miejsce starej i wykonaj obliczenie dla allPaths i pozostalych wymaganych wartosci


        end = clock();
        if(kstopu == '1' && double(end - begin) / CLOCKS_PER_SEC > ttime || kstopu == '3' && double(end - begin) / CLOCKS_PER_SEC > ttime)
            {keepGoing = false;
            std::cout << "\n warunek czasu, wykonywano przez: " << iteration;
            }
        if(kstopu == '2' && iteration >= maxiteration || kstopu == '3' && iteration >= maxiteration)
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

    delete[] visited;
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
    delete[] pOperator;
    delete[] bestPath;

    return bestCost;
}
