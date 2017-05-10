#include <iostream>
#include <chrono>
#include "Graph.h"
#include "GraphMatrix.h"
#include "GraphList.h"
#include "MinimumSpanningTree.h"
#include "ShortestPath.h"
#include "MaximumFlow.h"

void mainManu(Problem *p);
bool createFile(int numberOfVertexes, int numberofEdges);
void test();

int main() {
    srand(time(NULL));
    int n = 100;
    int density = 50;
    createFile(n,density);

    Problem *p = NULL;
    //p = new MaximumFlow();
    //p->test(0, 6);
    mainManu(p);
    //test();

    if (p!=NULL) delete p;
    return 0;
}

void test(){
    Problem *p = new MaximumFlow();
    std::ofstream fout;
    fout.open("results.txt");
    int size[] = {50,100,150,200,250};
    int densities[] = {25,50,75,99};
    bool reprezentation[] = {false, true};
    bool algorithms[] = {false, true};
    for (int i = 0; i < 2; i++){ //reprezentacja
        fout << "r:" << reprezentation[i] << endl;
        for (int j = 0; j < 4; j++){ //gestosc
            fout << "d:  " << densities[j] << endl;
            for (int k = 0; k < 2; k++){ //algorytmy
                fout << "a:    " << algorithms[k] << endl;
                for (int l = 0; l < 5; l++){ //wielkosc
                    createFile(size[l],densities[j]);
                    fout << "s:      " << size[l] << " "
                         << p->testTime(reprezentation[i],algorithms[k],rand()%size[l], rand()%size[l])
                         << endl;
                }
            }
        }
    }

    fout.close();
    delete p;
}

void mainManu(Problem *p) {
    std::cout << "MENU\n"
            "1. Minimalne drzewo rozpinajace.\n"
            "2. Najkrotsza sciezka w grafie.\n"
            "3. Maksymalny przeplyw.\n"
            "4. Wyjdz z programu.\n"
            "Prosze wpisac odpowiednia liczbe.";
    int chosen;
    std::cin >> chosen;
    switch(chosen){
        case 1:{
            Graph *gl = new GraphList();
            Graph *gm = new GraphMatrix();
            p = new MinimumSpanningTree();
            p->menu(gl, gm);
        }
            break;
        case 2: {
            Graph *gl = new GraphList();
            Graph *gm = new GraphMatrix();
            p = new ShortestPath();
            p->menu(gl, gm);
        }
            break;
        case 3:{
            Graph *gl = new GraphList();
            Graph *gm = new GraphMatrix();
            p = new MaximumFlow();
            p->menu(gl, gm);
        }
            break;
        case 4:
            if (p!=NULL) delete p;
            exit(0);
            break;
        default:
            cout << "Prosze podac poprawna liczbe.\n";
            cin.clear();
            cin.sync();
            break;
    }
    mainManu(p);
}

bool createFile(int numberOfVertexes, int density) {
    int numberOfEdges = density * (numberOfVertexes*numberOfVertexes-numberOfVertexes)/100;
    std::ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open()){
        fout << numberOfEdges << " " << numberOfVertexes << endl;
        for (int i = 0; i < numberOfEdges; i++){
            int start, end, length;
            do {
                start = i%numberOfVertexes;
                end = rand()%numberOfVertexes;
                length = rand()%100+1;
            }
            while(start == end);
            fout << start << " " << end << " " << length << endl;
        }
        fout.close();
        return true;
    }
    else return false;
}