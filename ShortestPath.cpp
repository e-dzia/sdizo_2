//
// Created by Edzia on 2017-04-30.
//

#include <sstream>
#include "ShortestPath.h"
#include "GraphList.h"
#include "GraphMatrix.h"
#include "Array2.h"

string ShortestPath::algorithm1(int start, int end) { //Dijkstra
/*
 * Tworzymy dwa zbiory wierzchołków notChecked i checked. Początkowo zbiór notChecked zawiera wszystkie wierzchołki grafu,
 * a zbiór checked jest pusty. Dla wszystkich wierzchołków u grafu za wyjątkiem startowego v
 * ustawiamy koszt dojścia length(u) na nieskończoność. Koszt dojścia length(v) zerujemy.
 * Dodatkowo ustawiamy poprzednik path(u) każdego wierzchołka u grafu na niezdefiniowany.
 * Poprzedniki będą wyznaczały w kierunku odwrotnym najkrótsze ścieżki od wierzchołków u
 * do wierzchołka startowego v. Teraz w pętli dopóki zbiór notChecked zawiera wierzchołki, wykonujemy następujące czynności:
 *      Wybieramy ze zbioru notChecked wierzchołek u o najmniejszym koszcie dojścia length(u).
 *      Wybrany wierzchołek u usuwamy ze zbioru notChecked i dodajemy do zbioru checked.
 *      Dla każdego sąsiada w wierzchołka u, który jest wciąż w zbiorze notChecked, sprawdzamy,
 *        czy length(w) > length(u) + waga krawędzi u–w. Jeśli tak, to wyznaczamy nowy koszt dojścia
 *        do wierzchołka w jako: length(w) ← length(u) + waga krawędzi u–w. Następnie wierzchołek u
 *        czynimy poprzednikiem w: path(w) ← u.
 */

    Array2 notChecked;
    Array2 checked;
    int length[g->getNumberOfVertexes()];
    int path[g->getNumberOfVertexes()];

    for (int i = 0; i < g->getNumberOfVertexes(); i++){
        notChecked.addElement(i,notChecked.getSize()+1);
        length[i] = INT32_MAX/2;
        path[i] = -1;
    }
    length[start] = 0;

    while(notChecked.getSize() > 0){
        int min =  INT32_MAX;
        int position = 0;
        for (int i = 0; i < g->getNumberOfVertexes(); i++){
            if (notChecked.findElement(i) != -1 && length[i] < min){
                min = length[i];
                position = i;
            }
        }
        checked.addElement(position,checked.getSize());
        notChecked.deleteElement(notChecked.findElement(position));

        Array2 *neighbours = g->getNeighbours(position); //1 - indeks sasiada, 2 - odleglosc

        for (int i = 0; i < neighbours[1].getSize(); i++){
            if (notChecked.findElement(neighbours[1][i]) != -1 && length[neighbours[1][i]] > length[position] + neighbours[2][i]){ //wciaz jest w notChecked
                length[neighbours[1][i]] = length[position] + neighbours[2][i];
                path[neighbours[1][i]] = position;
            }
        }
    }
    stringstream ss;

    //for (int i = 0; i < g->getNumberOfVertexes(); i++){
    if (path[end] == -1) {
        ss << "Nie ma takiej sciezki\n";
    }
    else{
        ss << end << " ";
        int j = end;
        while (path[j] != -1) {
            ss << path[j] << " ";
            j = path[j];
        }
        ss << " : " << length[end] << endl;
        //   }
    }

    string result = ss.str();

    return result;
}

std::string ShortestPath::algorithm2(int start, int end) { //Ford-Bellman
/*
 * Opisany tutaj algorytm będzie tworzył dwie n elementowe tablice danych (n oznacza liczbę wierzchołków w grafie):
 * length – element i-ty zawiera koszt dojścia z wierzchołka startowego do i-tego wierzchołka grafu po najkrótszej ścieżce.
 *      Dla wierzchołka startowego koszt dojścia wynosi 0.
 * path – element i-ty zawiera numer wierzchołka grafu, który jest poprzednikiem wierzchołka i-tego na najkrótszej ścieżce.
 *      Dla wierzchołka startowego poprzednikiem jest -1.
 * Na początku algorytmu ustawiamy wszystkie komórki tablicy length na największą możliwą wartość (oryginalnie na nieskończoność)
 * za wyjątkiem komórki odwzorowującej wierzchołek startowy, w której umieszczamy 0. Natomiast we wszystkich komórkach
 * tablicy path umieszczamy -1 (w grafie nie ma wierzchołka o numerze -1, oznacza to zatem brak poprzednika).
 * Następnie wykonujemy n - 1 obiegów pętli, w której dokonujemy relaksacji krawędzi
 * (każdy obieg ustala koszt dojścia do przynajmniej jednego wierzchołka grafu, ponieważ wierzchołek
 * startowy ma koszt 0, to pozostaje nam ustalenie kosztu jeszcze dla n - 1 wierzchołków, stąd wymagane
 * jest co najwyżej n - 1 obiegów pętli). Polega ona na tym, iż przeglądamy po kolei wszystkie krawędzie grafu.
 * Jeśli natrafimy na krawędź u–v o wadze w, dla której koszt dojścia length[v] jest większy od kosztu dojścia length[u] + w
 * (czyli dojście do wierzchołka v od wierzchołka u tą krawędzią jest tańsze od poprzednio znalezionych dojść),
 * to ustawiamy koszt length[v] na length[u] + w i w tablicy poprzedników dla path[v] umieszczamy numer wierzchołka u.
 * Gdy pętla wykona n - 1 obiegów, w tablicy length będziemy mieli koszty dojść do poszczególnych wierzchołków grafu
 * po najkrótszych ścieżkach, a w tablicy path dla każdego wierzchołka znajdziemy jego poprzednik na najkrótszej ścieżce
 * od wierzchołka startowego.
 */

    int length[g->getNumberOfVertexes()];
    int path[g->getNumberOfVertexes()];
    Array2 *edges = g->toArray();

    for (int i = 0; i < g->getNumberOfVertexes(); i++){
        length[i] = INT32_MAX/2;
        path[i] = -1;
    }
    length[start] = 0;

    for (int i = 0; i < g->getNumberOfVertexes()-1; i++){
        /*
         * relaksacja
         *      przegladamy po kolei krawedzie
         *      jesli krawedz u-v o wadze w ma length[v] > length[u]+w
         *          to length[v] = length[u]+w
         *          path[v] = u;
         */
        for (int j = 0; j < g->getNumberOfEdges(); j++){
            int u = edges[0][j];
            int v = edges[1][j];
            if (length[v] > length[u] + edges[2][j]){
                length[v] = length[u] + edges[2][j];
                path[v] = u;
            }
        }
    }


    stringstream ss;

    //for (int i = 0; i < g->getNumberOfVertexes(); i++){
    ss << end << " ";
    int j = end;
    while (path[j] != -1) {
        ss << path[j] << " ";
        j = path[j];
    }
    ss << " : " << length[end] << endl;
    //   }
    string result = ss.str();

    delete[] edges;

    return result;
}

void ShortestPath::menu() {
    std::cout << "MENU - Minimalne Drzewo Rozpinajace\n"
            "1. Reprezetacja listowa.\n"
            "2. Reprezentacja macierzowa.\n"
            "3. Wyjdz do glownego menu.\n"
            "Prosze wpisac odpowiednia liczbe.";
    int chosen;
    std::cin >> chosen;
    switch(chosen){
        case 1:
            g = new GraphList();
            this->menuFunctions();
            break;
        case 2:
            g = new GraphMatrix();
            this->menuFunctions();
            break;
        case 3:
            return;
        default:
            cout << "Prosze podac poprawna liczbe.\n";
            cin.clear();
            cin.sync();
            break;
    }
    this->menu();
}

void ShortestPath::menuFunctions() {
    std::cout << "MENU - Minimalne Drzewo Rozpinajace\n"
            "1. Wczytaj z pliku.\n"
            "2. Generuj losowo.\n"
            "3. Wyswietl.\n"
            "4. Algorytm Dijkstry.\n"
            "5. Algorytm Forda-Bellmana.\n"
            "6. Wyjdz do glownego menu.\n"
            "Prosze wpisac odpowiednia liczbe.\n";
    int chosen;
    std::cin >> chosen;
    switch(chosen){
        case 1:
            g->loadFromFile("data.txt");
            break;
        case 2:
            cout << "Prosze podac liczbe wierzcholkow.\n";
            int v;
            cin >> v;
            cout << "Prosze podac gestosc w procentach.\n";
            cin >> chosen;
            g->createRandom(v, chosen);
            break;
        case 3:
            cout << *g;
            break;
        case 4:{
            cout << "Prosze podac wierzcholek poczatkowy.\n";
            int start;
            cin >> start;
            cout << "Prosze podac wierzcholek koncowy.\n";
            int end;
            cin >> end;
            std::cout << this->algorithm1(start, end) << endl;
            break;
        }
        case 5: {
            cout << "Prosze podac wierzcholek poczatkowy.\n";
            int start;
            cin >> start;
            cout << "Prosze podac wierzcholek koncowy.\n";
            int end;
            cin >> end;
            std::cout << this->algorithm2(start, end) << endl;
            break;
        }
        case 6:
            return;
        default:
            cout << "Prosze podac poprawna liczbe.\n";
            cin.clear();
            cin.sync();
            break;
    }
    this->menuFunctions();
}

ShortestPath::~ShortestPath() {

}
