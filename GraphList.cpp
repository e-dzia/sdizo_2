//
// Created by Edzia on 2017-04-29.
//

#include "GraphList.h"

void GraphList::loadFromFile(std::string filename) {
    std::ifstream fin;
    fin.open(filename.c_str());
    fin >> edges;
    fin >> vertexes;
    this->countDensity();

    this->createList(vertexes);

    int startVertex;
    int endVertex;
    int length;
    for (int i = 0; i < edges; i++){
        fin >> startVertex;
        fin >> endVertex;
        fin >> length;
        if (list[startVertex].findElement(endVertex) == -1) //jesli nie sa polaczone
            list[startVertex].addElement(endVertex,length);
    }
    this->countEdges();
}

void GraphList::print(std::ostream &str) const {
    for (int i = 0; i < vertexes; i++){
        str << i << " " << list[i] << endl;
    }
}

void GraphList::countEdges() {
    int sum = 0;
    for (int i = 0; i < vertexes; i++){
        sum += list[i].getSize();
    }
    edges = sum;
}

GraphList::~GraphList() {
    if (list != NULL) delete[] list;
}

GraphList::GraphList() {
    vertexes = 0;
    edges = 0;
    density = 0;
    list = NULL;
}

void GraphList::createList(int size) {
    if (list != NULL) delete[] list;
    list = new List2[size];
}

void GraphList::createRandom(int vertexes, int density) {
    createList(vertexes);
    this->vertexes = vertexes;
    this->density = density;
    this->edges = ((vertexes*vertexes - vertexes) * density)/100;

    int startVertex;
    int endVertex;
    int length;
    bool again;
    for (int i = 0; i < edges; i++){
        do {
            again = true;
            startVertex = i%vertexes;
            endVertex = rand()%vertexes;
            length = rand()%10+1;

            if (startVertex != endVertex){
                if (list[startVertex].findElement(endVertex) == -1){ //jesli jeszcze nie jest sasiadem z danym wierzcholkiem
                    list[startVertex].addElement(endVertex,length);
                    again = false;
                }
            }
        }while (again);
    }
}

int** GraphList::toSortedArray() {
    int **result = new int*[edges];
    for (int i = 0; i < edges; i++){
        result[i] = new int[3]; // 0 - od, 1 - do, 2 - dlugosc
    }

    int index = 0;
    for (int i = 0; i < vertexes; i++){
        if (list[i].getSize() > 0){
            ElemList * el = list[i].getHead();
            while (el != NULL){
                result[index][0] = i;
                result[index][1] = el->neighbour;
                result[index][2] = el->length;
                el = el->next;
                index++;
            }
        }
    }

    //sortowanie babelkowe
    for (int i = 0; i < index; i++){
        for (int j = 0; j < index-1; j++){
            if (result[i][2] < result[j][2]){
                for (int k = 0; k <3; k++){
                    int tmp = result[i][k];
                    result[i][k] = result[j][k];
                    result[j][k] = tmp;
                }

            }
        }
    }

    return result;
}

Array2 * GraphList::getNeighbours(int index) {
    ElemList *elemList = list[index].getHead();
    Array2 *result = new Array2[3]; //1 -sasiad, 2 - dlugosc, 0-obecny wierzcholek

    while (elemList != NULL){
        if (result[1].findElement(elemList->neighbour) == -1){
            result[0].addElement(index,0);
            result[1].addElement(elemList->neighbour,0);
            result[2].addElement(elemList->length,0);
        }
        elemList = elemList->next;
    }

    return result;
}

void GraphList::makeBothWays() {
    for (int i = 0; i < this->vertexes; i++){
        ElemList *p = this->list[i].getHead();
        while(p != NULL){
            if (this->list[p->neighbour].findElement(i) == -1){
                this->list[p->neighbour].addElement(i,p->length);
            }
            else this->list[p->neighbour].getPointerElement(this->list[p->neighbour].findElement(i))->length =
                         this->list[i].getPointerElement(this->list[i].findElement(p->neighbour))->length;

            p = p->next;
        }
    }
    this->countEdges();
}

Array2 *GraphList::toArray() {
    Array2 *l = new Array2[3];

    for (int i = 0; i < vertexes; i++){
        if (list[i].getSize() > 0){
            ElemList * el = list[i].getHead();
            while (el != NULL){
                l[0].addElement(i,0);
                l[1].addElement(el->neighbour,0);
                l[2].addElement(el->length,0);
                el = el->next;
            }
        }
    }
    return l;
}

void GraphList::setEdge(int start, int end, int length) {
    if (list[start].findElement(end) == -1){
        list[start].addElement(end,length);
    }
    else list[start].getPointerElement(end)->length = length;
}

int GraphList::getEdgeLength(int start, int end) {
    if (list[start].findElement(end) != -1)
        return list[start].getPointerElement(end)->length;
    else
        return 0;
}
