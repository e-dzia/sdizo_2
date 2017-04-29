//
// Created by Edzia on 2017-04-29.
//

#include "Graph.h"


int Graph::getDensity() {
    return density;
}

void Graph::countDensity() {
    if (vertexes != 0)
        density = edges/vertexes*100;
    else density = 0;
}

Graph::~Graph() {
    vertexes = 0;
    edges = 0;
    density = 0;
}

int Graph::getVertexes() const {
    return vertexes;
}

int Graph::getEdges() const {
    return edges;
}
