//
// Created by Edzia on 2017-03-06.
//

#ifndef SDIZO_2_LIST_H
#define SDIZO_2_LIST_H

#include <iostream>
#include <fstream

using namespace std;

struct ElemList{
    int length;
    int neighbour;
    ElemList * next;
    ElemList * prev;
};


class List{
private:
    ElemList * head;
public:
    ElemList *getHead() const;

private:
    int size;
public:
    List(); //konstruktor domyślny
    ~List(); //destruktor

    int getSize() const;

    void loadFile(string name);
    void addElement(int afterValue, int value); //za afterValue trzeba wstawic value
    void deleteElement(int value); //podana wartosc do usuniecia
    int findElement(int value);

    int getElement(int position);

    friend ostream & operator<<(ostream & os , const List & a);

    void menu();

    void print(std::ostream &str) const;
};

#endif //SDIZO_2_LIST_H
