//
// Created by Edzia on 2017-03-06.
//

#ifndef SDIZO_2_ARRAY_H
#define SDIZO_2_ARRAY_H

#include <iostream>
#include <fstream>

using namespace std;

class Array{
private:
    int size;
    int * array;
public:
    Array(); //konstruktor domyślny
    ~Array(); //destruktor

    int getSize()const;

    void loadFile(string name);
    void addElement(int value, int position); //wartosc i pozycja, na ktora trzeba ja wstawic
    void deleteElement(int position); //podana pozycja elementu do usuniecia
    int findElement(int value);

    friend ostream & operator<<(ostream & os , const Array & a);

    int & operator[](int n);
    int & operator[](int n) const;

    void menu();

    void print(std::ostream &str) const ;

    bool deleteAll();

    int getElement(int position);
};


#endif //SDIZO_2_ARRAY_H