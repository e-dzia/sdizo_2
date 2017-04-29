//
// Created by Edzia on 2017-04-29.
//

#ifndef SDIZO_2_GRAPHLIST_H
#define SDIZO_2_GRAPHLIST_H


#include "Graph.h"

class GraphList: public Graph {
private:

public:
    void loadFromFile(std::string filename) override;

    void print(std::ostream &str) const override;
};


#endif //SDIZO_2_GRAPHLIST_H
