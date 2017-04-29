#include <iostream>
#include "Graph.h"
#include "GraphMatrix.h"

int main() {
    Graph *g = new GraphMatrix();
    g->loadFromFile("data.txt");
    std::cout << *g;
    return 0;
}