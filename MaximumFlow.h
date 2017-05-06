//
// Created by Edzia on 2017-05-03.
//

#ifndef SDIZO_2_MAXIMUMFLOW_H
#define SDIZO_2_MAXIMUMFLOW_H


#include "Problem.h"

class MaximumFlow: public Problem {
public:
    string algorithm1(int start, int end) override;

    string algorithm2(int start, int end) override;

    void menu(Graph *gl, Graph *gm) override;

    bool dfs(int start, int end, int* path);
    void dfs_recursive(int i, int *path, bool* visited);

    bool bfs(int start, int end, int* path);

};


#endif //SDIZO_2_MAXIMUMFLOW_H
