//
// Created by Edzia on 2017-04-30.
//

#ifndef SDIZO_2_SHORTESTPATH_H
#define SDIZO_2_SHORTESTPATH_H


#include "Problem.h"
#include "Graph.h"

class ShortestPath: public Problem {
private:

public:
    ~ShortestPath();

    string algorithm1(int start, int end) override; //Dijkstra

    std::string algorithm2(int start, int end) override; //Ford-Bellman

    void menu(Graph *gl, Graph *gm) override;


};


#endif //SDIZO_2_SHORTESTPATH_H
