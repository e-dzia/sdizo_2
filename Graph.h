//
// Created by Edzia on 2017-04-29.
//
#include <iostream>

#ifndef SDIZO_2_GRAPH_H
#define SDIZO_2_GRAPH_H


class Graph {
protected:
    int vertexes;//liczba wierzcholkow
    int edges; //liczba krawedzi
    int density; //gestosc

public:
    virtual ~Graph();

    int getDensity();
    int getVertexes() const;
    int getEdges() const;

    virtual void countDensity();
    virtual void countEdges() = 0;
    virtual void loadFromFile(std::string filename) = 0;
    virtual void print(std::ostream& str)const = 0;

    friend std::ostream& operator<<(std::ostream& str, Graph const& g){
        g.print(str);
        return str;
    }
};


#endif //SDIZO_2_GRAPH_H
