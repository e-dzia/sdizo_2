//
// Created by Edzia on 2017-04-30.
//

#ifndef SDIZO_2_PROBLEM_H
#define SDIZO_2_PROBLEM_H


#include "Graph.h"

class Problem {
protected:
    Graph *g;
public:
    virtual ~Problem(); //no problem

    virtual string algorithm1(int start, int end)= 0;

    virtual std::string algorithm2(int start, int end)= 0;

    virtual void menu(Graph *gl, Graph *gm)= 0;

    void test(int start, int end);

    double testTime(bool matrix, bool algorithm2, int start, int end);

};


#endif //SDIZO_2_PROBLEM_H
