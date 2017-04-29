//
// Created by Edzia on 2017-04-29.
//

#include "GraphMatrix.h"
#include <fstream>

GraphMatrix::GraphMatrix() {
    vertexes = 0;
    edges = 0;
    density = 0;
}

GraphMatrix::GraphMatrix(int size) {
    matrix = new int *[size];
    for (int i = 0; i < size; i++){
        matrix[i] = new int[size];
    };
    vertexes = size;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (i==j) matrix[i][j] = -1;
            else
                matrix[i][j] = rand()%10;
        }
    }
}

GraphMatrix::~GraphMatrix() {
    for (int i = 0; i < vertexes; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
}

void GraphMatrix::loadFromFile(std::string filename) {
    std::ifstream fin;
    fin.open(filename.c_str());
    fin >> edges;
    fin >> vertexes;

    this->createMatrix(vertexes);

    int startVertex;
    int endVertex;
    int length;
    for (int i = 0; i < edges; i++){
        fin >> startVertex;
        fin >> endVertex;
        fin >> length;
        matrix[startVertex][endVertex] = length;
    }


}

void GraphMatrix::print(std::ostream &str) const {
    str.flags ( std::ios::right);
    str.width (4);
    str << "    ";
    for (int i = 0; i < vertexes; i++){
        str.width (4);
        str << i << " ";
    }
    str << std::endl;
    for (int i = 0; i < vertexes; i++){
        str.width (4);
        str << i << "  ";
        for (int j = 0; j < vertexes; j++){
            str.width (4);
            str << matrix[i][j] << " ";
        }
        str << std::endl;
    }
}

void GraphMatrix::createMatrix(int v) {
    matrix = new int *[v];
    for (int i = 0; i < v; i++){
        matrix[i] = new int[v];
    };
    for (int i = 0; i < v; i++){
        for (int j = 0; j < v; j++){
            matrix[i][j] = 0;
        }
    }
}

void GraphMatrix::countEdges() {
    for (int i = 0; i < vertexes; i++){
        for (int j = 0; j < i; j++){
            if (matrix[i][j] != 0 || matrix[j][i] != 0)
                edges++;
        }
    }
}


