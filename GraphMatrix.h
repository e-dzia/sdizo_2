//
// Created by Edzia on 2017-04-29.
//

#ifndef SDIZO_2_GRAPHMATRIX_H
#define SDIZO_2_GRAPHMATRIX_H


#include "Graph.h"

class GraphMatrix: public Graph{
private:
    int **matrix;
public:
    GraphMatrix();
    GraphMatrix(int size);
    ~GraphMatrix();

    void loadFromFile(std::string filename) override;
    void print(std::ostream &str) const override;

    void createMatrix(int size);

    void countEdges() override;

};


#endif //SDIZO_2_GRAPHMATRIX_H
