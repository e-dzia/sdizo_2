//
// Created by Edzia on 2017-04-30.
//

#include <sstream>
#include "MinimumSpanningTree.h"
#include "GraphList.h"
#include "GraphMatrix.h"
#include "Array2.h"

std::string MinimumSpanningTree::algorithm1(int start, int end) { //Prim
    /*
     * Wybieramy w grafie dowolny wierzchołek startowy.
     * Dopóki drzewo nie pokrywa całego grafu,
     *      znajdujemy krawędź o najniższym koszcie
     *      spośród wszystkich krawędzi prowadzących od wybranych już wierzchołków do wierzchołków
     *      jeszcze niewybranych.
     *      Znalezioną krawędź dodajemy do drzewa rozpinającego.
     */
    g->makeBothWays();
    //cout << g->getNumberOfEdges() << endl << *g << endl;
    int MST[g->getNumberOfEdges()][3]; //pusta tablica krawedzi
    bool isVertexInMST[g->getNumberOfVertexes()]; //czy dany wierzcholek jest w MST
    int numberOfVertexesInMST = 0;
    //int **sortedEdges = g->toSortedArray(); //tablica wszystkich krawedzi grafu posortowana wg dlugosci

    //Array2 *setsOfVertexes = new Array2[g->getNumberOfVertexes()];
    Array2 *arrayOfEdges;

    for (int i = 0; i < g->getNumberOfEdges(); i++){
        for (int j = 0; j <3; j++)
            MST[i][j] = 0;
    }
    for (int i = 0; i < g->getNumberOfVertexes(); i++){
        isVertexInMST[i] = false;
        //setsOfVertexes[i].addElement(i,0);
    }

    int j = 0;//indeks w MST
    isVertexInMST[0] = true;
    numberOfVertexesInMST++;
    arrayOfEdges = g->getNeighbours(0); //1 -sasiad, 2 - dlugosc, 0-obecny wierzcholek

    while(numberOfVertexesInMST < g->getNumberOfVertexes()){
        //znajdz krawedz o najnizszym koszcie ktora idzie od wybranego do niewybranego i dodaj ja do MST
        int min = INT32_MAX;
        int position = 0;
        int edgePosition = 0;
        for (int i = 0; i < arrayOfEdges->getSize(); i++){
            if ((!isVertexInMST[arrayOfEdges[1][i]]) && arrayOfEdges[2][i] < min){
                min = arrayOfEdges[2][i];
                position = arrayOfEdges[1][i];
                edgePosition = i;
            }
        }
        for (int k = 0; k <3; k++)
            MST[j][k] = arrayOfEdges[k][edgePosition]; //wpisz to do MST
        j++;
        numberOfVertexesInMST++;
        isVertexInMST[position] = true;
        isVertexInMST[arrayOfEdges[1][edgePosition]] = true;

        Array2 *newArray = g->getNeighbours(position);
        arrayOfEdges[0].merge(newArray);
        arrayOfEdges[1].merge(newArray+1);
        arrayOfEdges[2].merge(newArray+2);
        delete[] newArray;
    }


    int sum = 0;
    for (int i = 0; i < g->getNumberOfEdges(); i++){
        sum += MST[i][2];
    }

    stringstream ss;
    /*for (int i = 0; i < j; i++){
        ss << MST[i][0] << " " << MST[i][1] << " " << MST[i][2] << endl;
    }*/
    ss << "Suma wag: " << sum << endl;
    string result = ss.str();

    //delete[] setsOfVertexes;

   /* for (int i = 0; i < g->getNumberOfEdges(); i++){
        delete[] sortedEdges[i];
    }
    delete[] sortedEdges;*/

    return result;
}

std::string MinimumSpanningTree::algorithm2(int start, int end) { //Kruskal
/*
 * Tworzymy pusty zbiór krawędzi MST oraz listę sortedEdges wszystkich krawędzi grafu uporządkowaną według rosnących wag.
 * Dopóki w MST nie mamy wszystkich wierzchołków grafu, wybieramy z listy sortedEdges krawędź i,
 *    jeśli nie tworzy ona cyklu z krawędziami już obecnymi w MST, dodajemy ją do zbioru MST.
 *    (Cykl - kiedy wierzchołek startVertex i endVertex sa juz w tym samym poddrzewie MST)
 * Gdy algorytm zakończy pracę, w MST będzie minimalne drzewo rozpinające.
 */
    g->makeBothWays();
    //cout << g->getNumberOfEdges() << endl << *g << endl;
    int MST[g->getNumberOfEdges()][3]; //pusta tablica krawedzi
    bool isVertexInMST[g->getNumberOfVertexes()]; //czy dany wierzcholek jest w MST
    int **sortedEdges = g->toSortedArray(); //tablica wszystkich krawedzi grafu posortowana wg dlugosci
    Array2 *setsOfVertexes = new Array2[g->getNumberOfVertexes()];

    for (int i = 0; i < g->getNumberOfEdges(); i++){
        for (int j = 0; j <3; j++)
            MST[i][j] = 0;
    }
    for (int i = 0; i < g->getNumberOfVertexes(); i++){
        isVertexInMST[i] = false;
        setsOfVertexes[i].addElement(i,0);
    }

    int j = 0;//indeks w MST

    for (int i = 0; i < g->getNumberOfEdges(); i++){
        int u = sortedEdges[i][0];
        int v = sortedEdges[i][1];
        Array2 *arrayOfU;
        for (int k = 0; k < g->getNumberOfVertexes(); k++){
            if (setsOfVertexes[k].findElement(u) != -1)
                arrayOfU = &(setsOfVertexes[k]);
        }

        if (arrayOfU->findElement(v) == -1) {
            for (int k = 0; k <3; k++)
                MST[j][k] = sortedEdges[i][k]; //wpisz to do MST
            j++;

            Array2 *arrayOfV;
            for (int k = 0; k < g->getNumberOfVertexes(); k++){
                if (setsOfVertexes[k].findElement(v) != -1)
                    arrayOfV = &(setsOfVertexes[k]);
            }

            arrayOfU->merge(arrayOfV);

            /*for (int l = 0; l < g->getNumberOfVertexes(); l++){
                cout << setsOfVertexes[l] << "  " << l << " ####################\n";
            }
            cout << "####################\n";*/
        }

    }

    int sum = 0;
    for (int i = 0; i < g->getNumberOfEdges(); i++){
        sum += MST[i][2];
    }

    //std::string result;

    stringstream ss;

    /*for (int i = 0; i < j; i++){
        ss << MST[i][0] << " " << MST[i][1] << " " << MST[i][2] << endl;
    }*/
    ss << "Suma wag: " << sum << endl;
    string result = ss.str();

    /*for (int i = 0; i < j; i++){
        std::cout << MST[i][0] << " " << MST[i][1] << " " << MST[i][2] << endl;
    }
*/
    delete[] setsOfVertexes;

    for (int i = 0; i < g->getNumberOfEdges(); i++){
        delete[] sortedEdges[i];
    }
    delete[] sortedEdges;

    return result;
}

void MinimumSpanningTree::menu() {
    //g = new GraphList();
    //gm = new GraphMatrix();

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

void MinimumSpanningTree::menuFunctions() {
    std::cout << "MENU - Minimalne Drzewo Rozpinajace\n"
            "1. Wczytaj z pliku.\n"
            "2. Generuj losowo.\n"
            "3. Wyswietl.\n"
            "4. Algorytm Prima.\n"
            "5. Algorytm Kruskala.\n"
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
        case 4:
            std::cout << this->algorithm1(0, 0) << endl;
            break;
        case 5:
            std::cout << this->algorithm2(0, 0) << endl;
            break;
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

MinimumSpanningTree::~MinimumSpanningTree() {

}


