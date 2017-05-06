//
// Created by Edzia on 2017-03-15.
//

#include "Array2.h"
#include <iostream>
#include <fstream>
#include <cstring>

Array2::Array2() {
    this->size = 0;
    this->array = new int[this->size];
}

Array2::~Array2() {
    this->size = 0;
    delete [] array;
    array = NULL;
}

int Array2::getSize()const {
    return this->size;
}

void Array2::addElement(int value, int position) {
    int * newArray = new int [this->getSize() +1]; //tworzy nowa tabele wieksza o 1 od obecnej
    if (position == 0){ //poczatek tabeli
        newArray[0] = value; //do miejsca na poczatku wpisuje (value)
        /*for (int i = 1; i < this->getSize() + 1; i++) {
            newArray[i] = this->array[i - 1]; //do pozostalych miejsc wpisuje pozostałe wartosi po kolei
        }*/
        if( this->array != NULL ) memcpy(newArray+1, this->array, this->getSize()*sizeof(int));
    }
    else if (position >= this->getSize()){ //koniec tabeli
        /*for (int i = 0; i < this->getSize(); i++){
            newArray[i] = this->array[i]; //przepisuje elementy tablicy do nowej
        }*/
        if( this->array != NULL ) memcpy(newArray, this->array, this->getSize()*sizeof(int));
        newArray[this->getSize()] = value; // dopisuje na koniec listy wartosc (value)
    }
    else {//inne miejsce tabeli
        int i = 0;
        /*for (; i < position; i++){
            newArray[i] = this->array[i]; //do miejsca (position) przepisuje elementy
        }*/
        if( this->array != NULL ) memcpy(newArray, this->array, position*sizeof(int));
        newArray[position] = value; //w miejsce (position) wpisuje wartosc (value)
        if( this->array != NULL ) memcpy(newArray + position+1, this->array+position,(this->getSize()-position)*sizeof(int));
        /*for (; i < this->getSize()+1; i++){
            newArray[i] = this->array[i-1]; //do reszty tablicy wpisuje dalsze elementy starej tablicy
        }*/
    }
    this->size++; //zwieksza (size)
    delete [] this->array; //usuwa stara tablice
    this->array = newArray; //do starej przypisuje nowa
}

void Array2::deleteElement(int position) {
    if (position > this->getSize()-1) return;
    if (size == 0) return;
    int * newArray = new int [this->getSize() -1]; //tworzy nowa tabele mniejsza o 1 od obecnej
    this->size--;
    if (position == 0){ //poczatek tabeli
        /*for (int i = 1; i <= this->getSize(); i++){
            newArray[i-1] = this->array[i]; //do pozostalych miejsc wpisuje pozostałe wartosi (oprocz indeksu 0) po kolei
        }*/
        memcpy(newArray,this->array+1,this->getSize()*sizeof(int));
    }
    else if (position == this->getSize()){ //koniec tabeli
        /*for (int i = 0; i <= this->getSize()-1; i++){
            newArray[i] = this->array[i]; //przepisuje elementy tablicy do nowej, bez ostatniego
        }*/
        memcpy(newArray,this->array,this->getSize()*sizeof(int));
    }
    else {//inne miejsce tabeli
        /* int i = 0;
         for (; i < position; i++){
             newArray[i] = this->array[i]; //do miejsca (position) przepisuje elementy
         }
         for (; i < this->getSize(); i++){
             newArray[i] = this->array[i+1]; //do reszty tablicy wpisuje dalsze elementy starej tablicy oprócz tego usuniętego
         }*/
        memcpy(newArray,this->array,(position)*sizeof(int));
        memcpy(newArray + position,this->array + position + 1,(this->getSize()-position)*sizeof(int));
    }

    delete [] this->array; //usuwa stara tablice
    array = newArray; //do starej przypisuje nowa
   // if (this->size == 0) array = NULL;
}

int Array2::findElement(int value) {
    for (int i = 0; i < this->getSize(); i++){
        if (this->array[i] == value) return i;
    }
    return -1;
}

ostream & operator<< ( ostream & os , const Array2 & a ){
    for (int i = 0; i < a.getSize(); i++){
        os << a.array[i] << " ";
    }
    return os;
}

void Array2::loadFile(string name) {
    ifstream fin;
    fin.open(name.c_str(), ios::in);
    if (fin.is_open()){
        int size = 0;
        fin >> size;
        for (int i = 0; i < size; i++){
            int element;
            fin >> element;
            this->addElement(element,this->getSize());
        }
        fin.close();
    }
}

int& Array2::operator[](int n) {
    return array[n];
}

int &Array2::operator[](int n) const {
    return array[n];
}

void Array2::print(std::ostream &str) const {
    str << *this;
}

void Array2::menu() {
    cout << "MENU - tablica\n"
            "1. Zbuduj z pliku.\n"
            "2. Usun.\n"
            "3. Dodaj.\n"
            "4. Znajdz.\n"
            "5. Wyswietl.\n"
            "6. Wyjdz do glownego menu.\n"
            "Prosze wpisac odpowiednia liczbe.";
    int chosen;
    cin >> chosen;
    switch(chosen){
        case 1:
            this->loadFile("numbers.txt");
            break;
        case 2:
            cout << "Prosze podac pozycje liczby do usuniecia.\n";
            int position;
            cin >> position;
            this->deleteElement(position);
            break;
        case 3:
            cout << "Prosze podac liczbe do wpisania.\n";
            cin >> position;
            cout << "Prosze podac pozycje do wpisania liczby.\n";
            int number;
            cin >> number;
            this->addElement(position,number);
            break;
        case 4:
            cout << "Prosze podac liczbe do znalezienia.\n";
            cin >> number;
            if (this->findElement(number)!=-1)
                cout << "Znaleziono.\n";
            else cout << "Nie znaleziono.\n";
            break;
        case 5:
            cout << *this << endl;
            break;
        case 6:
            return;
        default:
            cout << "Prosze podac poprawna liczbe.\n";
            cin.clear();
            cin.sync();
            break;
    }
    this->menu();
}

int Array2::getElement(int position) {
    if (position < this->size && position >= 0)
        return array[position];
    else return -1;
}

void Array2::merge(Array2 *a) {
    while(a->getSize() > 0){
        this->addElement(a->getElement(0),0);
        a->deleteElement(0);
    }
}

void Array2::sort() {
//sortowanie babelkowe
    for (int i = 0; i < this->getSize(); i++){
        for (int j = 0; j < this->getSize()-1; j++){
            if (this->array[i] < this->array[j]){
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
    }
}
