//
// Created by Edzia on 2017-03-06.
//

#ifndef SDIZO_2_ARRAY_H
#define SDIZO_2_ARRAY_H

#include <iostream>
#include <fstream>

using namespace std;

class Array2{
private:
    int size;
    int * array;
public:
    Array2(); //konstruktor domyślny
    ~Array2(); //destruktor

    int getSize()const;

    void loadFile(string name);
    void addElement(int value, int position); //wartosc i pozycja, na ktora trzeba ja wstawic
    void deleteElement(int position); //podana pozycja elementu do usuniecia
    int findElement(int value);

    friend ostream & operator<<(ostream & os , const Array2 & a);

    void merge(Array2 *a);
    void sort();

    int & operator[](int n);
    int & operator[](int n) const;

    void menu();

    void print(std::ostream &str) const ;

   // bool deleteAll();

    int getElement(int position);
};


#endif //SDIZO_2_ARRAY_H