//
// Created by Edzia on 2017-04-30.
//

#ifndef SDIZO_2_MINIMUMSPANNINGTREE_H
#define SDIZO_2_MINIMUMSPANNINGTREE_H


#include "Graph.h"
#include "Problem.h"

class MinimumSpanningTree: public Problem {
private:
    //Graph *g;
public:
    ~MinimumSpanningTree();

    std::string algorithm1(int start, int end); //Prim
    std::string algorithm2(int start, int end); //Kruskal

    void menu();

    void menuFunctions();
};


#endif //SDIZO_2_MINIMUMSPANNINGTREE_H
