//
// Created by Edzia on 2017-04-29.
//

#ifndef SDIZO_2_GRAPHLIST_H
#define SDIZO_2_GRAPHLIST_H


#include "Graph.h"
#include "List2.h"


class GraphList: public Graph {
private:
    List2 *list;
    void countEdges() override;
    void createList(int size);

public:
    GraphList();
    ~GraphList();

    void loadFromFile(std::string filename) override;
    void print(std::ostream &str) const override;

    void createRandom(int vertexes, int density) override;

    int** toSortedArray() override;

    Array2 * getNeighbours(int index) override;

    void makeBothWays() override;

    Array2 *toArray() override;

    void setEdge(int start, int end, int length) override;

    int getEdgeLength(int start, int end) override;
};


#endif //SDIZO_2_GRAPHLIST_H
