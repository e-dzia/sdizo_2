//
// Created by Edzia on 2017-05-03.
//

#include <sstream>
#include <chrono>
#include "MaximumFlow.h"

string MaximumFlow::algorithm1(int start, int end) { //w głąb

    /*
     * PRZESZUKIWANIE W GLAB
     * Zaznaczamy bieżący wierzchołek jako odwiedzony. Przechodzimy do kolejnych sąsiadów wierzchołka bieżącego
     * i wykonujemy dla nich tą samą operację (tzn. zaznaczamy je jako odwiedzone i przechodzimy do ich sąsiadów).
     * Przechodzenie kończymy, gdy zostaną w ten sposób odwiedzone wszystkie dostępne wierzchołki.
     */

    /*
     * Wyzeruj wszystkie przepływy w sieci
     * Dopóki w sieci rezydualnej istnieje ścieżka rozszerzająca p,
     *      zwiększaj przepływ o cf(p) wzdłuż kanałów zgodnych z kierunkiem ścieżki,
     *      a zmniejszaj przepływ wzdłuż kanałów przeciwnych (wygaszanie przepływu).
     *      Przepływ sieciowy rośnie o cf(p).
     */

    int flow = 0;
    bool visited[g->getNumberOfVertexes()] = {0};
    int path[g->getNumberOfVertexes()];

    Array2 *arrayOfEdges = nullptr;

    for (int i = 0; i < g->getNumberOfVertexes();i++){
        path[i] = -1;
    }

    while(dfs(start,end,path)){
        for (int i = 0; i < g->getNumberOfVertexes(); i++){
            cout << "&&& " << i << " " << path[i] << endl;
        }
        int j = end;
        while (j != -1){
            cout << j << " ";
            j = path[j];
        }
        cout << endl;
        j = end;
        while (j != -1){

            j = path[j];
        }

        for (int i = 0; i < g->getNumberOfVertexes();i++){
            path[i] = -1;
        }
    }

/*    for (int i = 0; i < g->getNumberOfVertexes();i++){
        if (dfs(start,end,path)){

        }

        if (arrayOfEdges != nullptr)
            delete[] arrayOfEdges;
    }*/


    stringstream ss;
    /*for (int i = 0; i < j; i++){
        ss << MST[i][0] << " " << MST[i][1] << " " << MST[i][2] << endl;
    }*/
    //ss << "Suma wag: " << sum << endl;
    string result = ss.str();

    return result;
}

string MaximumFlow::algorithm2(int start, int end) { //wszerz
    return " ";
}

void MaximumFlow::menu(Graph *gl, Graph *gm) {
    std::chrono::nanoseconds time_start;
    std::chrono::nanoseconds time_end;
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
            gl->loadFromFile("data.txt");
            gm->loadFromFile("data.txt");
            break;
        case 2:
            cout << "Prosze podac liczbe wierzcholkow.\n";
            int v;
            cin >> v;
            cout << "Prosze podac gestosc w procentach.\n";
            cin >> chosen;
            gl->createRandom(v, chosen);
            gm->createRandom(v, chosen);
            break;
        case 3:
            g = gl;
            cout << "Reprezentacja listowa:\n" << *g << endl;
            g = gm;
            cout << "Reprezentacja macierzowa:\n" << *g << endl;
            g = NULL;
            break;
        case 4:{
            cout << "Prosze podac wierzcholek poczatkowy.\n";
            int start;
            cin >> start;
            cout << "Prosze podac wierzcholek koncowy.\n";
            int end;
            cin >> end;
            g = gl;
            time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            std::cout << "\n########################################\nReprezentacja listowa:\n" << this->algorithm1(start, end);
            time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            cout << "Czas: " << (time_end - time_start) / std::chrono::nanoseconds(1) << " nanosekund.\n";
            g = gm;
            time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            std::cout << "\n########################################\nReprezentacja macierzowa:\n" << this->algorithm1(start, end);
            time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            cout << "Czas: " << (time_end - time_start) / std::chrono::nanoseconds(1) << " nanosekund.\n";
            g = NULL;
            break;
        }
        case 5: {
            cout << "Prosze podac wierzcholek poczatkowy.\n";
            int start;
            cin >> start;
            cout << "Prosze podac wierzcholek koncowy.\n";
            int end;
            cin >> end;
            g = gl;
            time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            std::cout << "\n########################################\nReprezentacja listowa:\n" << this->algorithm2(start, end);
            time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            cout << "Czas: " << (time_end - time_start) / std::chrono::nanoseconds(1) << " nanosekund.\n";
            g = gm;
            time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            std::cout << "\n########################################\nReprezentacja macierzowa:\n" << this->algorithm2(start, end);
            time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            cout << "Czas: " << (time_end - time_start) / std::chrono::nanoseconds(1) << " nanosekund.\n";
            g = NULL;
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
    this->menu(gl, gm);
}

bool MaximumFlow::dfs(int start, int end, int* path) {
    /*
     *  	Zaznaczamy bieżący wierzchołek jako odwiedzony. Przechodzimy do kolejnych sąsiadów wierzchołka bieżącego
     *  	i wykonujemy dla nich tą samą operację (tzn. zaznaczamy je jako odwiedzone i przechodzimy do ich sąsiadów).
     *  	Przechodzenie kończymy, gdy zostaną w ten sposób odwiedzone wszystkie dostępne wierzchołki.
     */

    bool visited[g->getNumberOfVertexes()] = {0};
    visited[start] = true;
    bool allVisited = false;
    Array2 arrayOfNeighbours;
    arrayOfNeighbours.addElement(start,0);

    while (!allVisited){
        int u = arrayOfNeighbours.getElement(arrayOfNeighbours.getSize()-1); //wez pierwszego sasiada
        arrayOfNeighbours.deleteElement(arrayOfNeighbours.getSize()-1);

        visited[u] = true;
        Array2 * array2 = g->getNeighbours(u);
        int size = array2[1].getSize();
        for (int j = 0; j < size; j++){
            if (!visited[array2[1][j]]){
                arrayOfNeighbours.addElement(array2[1][j],0);
                path[array2[1][j]] = u;
                visited[array2[1][j]] = true;
            }

        }

        allVisited = true;
        for (int i = 0; i < g->getNumberOfVertexes(); i++){
            if (!visited[i])
                allVisited = false;
        }
        if (array2 != nullptr) delete array2;
    }

    return (visited[end]);

    return false;
}
