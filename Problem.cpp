//
// Created by Edzia on 2017-04-30.
//

#include <chrono>
#include "Problem.h"
#include "GraphMatrix.h"
#include "GraphList.h"

void Problem::test(int start, int end) {
    g = new GraphMatrix();
    g->loadFromFile("data.txt");
    //std::cout << *g << endl;
    std::cout << "Reprezentacja macierzowa.\n";
    std::cout << "#############################\nAlgorytm1:\n";
    std::cout << this->algorithm1(start, end);

    g->loadFromFile("data.txt");
    //std::cout << *g << endl;
    std::cout << "\n#############################\nAlgorytm2:\n";
    std::cout << this->algorithm2(start, end);
    delete g;
    g = NULL;

    g = new GraphList();
    g->loadFromFile("data.txt");
    //std::cout << *g << endl;
    std::cout << "\n#############################\nReprezentacja listowa.\n";
    std::cout << "Algorytm1:\n";
    std::cout << this->algorithm1(start, end);

    g->loadFromFile("data.txt");
    //std::cout << *g << endl;
    std::cout << "\n#############################\nAlgorytm2:\n";
    std::cout << this->algorithm2(start, end);
    delete g;
    g = NULL;

}

Problem::~Problem() {
    if (g != NULL)
        delete g;
    g = NULL;
}

double Problem::testTime(bool matrix, bool algorithm2, int start, int end) {
    std::chrono::nanoseconds time_start;
    std::chrono::nanoseconds time_end;
    //double time_duration;
    if (matrix){
        g = new GraphMatrix();
    }
    else {
        g = new GraphList();
    }
    g->loadFromFile("data.txt");
    if (algorithm2){
        time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch());
        this->algorithm2(start, end);
        time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch());
    }
    else{
        time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch());
        this->algorithm1(start, end);
        time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch());
    }

    return (time_end - time_start) / std::chrono::nanoseconds(1);
}

