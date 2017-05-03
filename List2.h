//
// Created by Edzia on 2017-03-06.
//

#ifndef SDIZO_2_LIST_H
#define SDIZO_2_LIST_H

#include <iostream>
#include <fstream>

using namespace std;

struct ElemList{
    int length;
    int neighbour;
    ElemList * next;
    ElemList * prev;
};


class List2{
private:
    ElemList * head;
public:
    ElemList *getHead() const;
    ElemList *getPointerElement(int position);

private:
    int size;
public:
    List2(); //konstruktor domyślny
    ~List2(); //destruktor

    int getSize() const;

    void loadFile(string name);
    void addElement(int neighbour, int length); //za afterValue trzeba wstawic value
    void deleteElement(int value); //podana wartosc do usuniecia
    int findElement(int value);

    int getElement(int position);

    friend ostream & operator<<(ostream & os , const List2 & a);

    void menu();

    void print(std::ostream &str) const;
};

#endif //SDIZO_2_LIST_H
