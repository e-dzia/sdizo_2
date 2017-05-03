//
// Created by Edzia on 2017-03-06.
//

#include "List2.h"

List2::List2() {
    this->head = NULL;
    size = 0;
}

List2::~List2() {
    ElemList * p = this->head;
    ElemList * next;
    while (p != NULL){
        next = p->next;
        delete p;
        p = next;

    }
    delete next;
    delete p;
}

void List2::loadFile(string name) {
    ifstream fin;
    fin.open(name.c_str(), ios::in);
    if (fin.is_open()){
        int size = 0;
        fin >> size;
        for (int i = 0; i < size; i++){
            int element;
            fin >> element;
            this->addElement(-1,element);
        }
        fin.close();
    }
}

void List2::addElement(int neighbour, int length) {
    int position = 0;
    ElemList * newElemList = new ElemList();
    newElemList->length = length;
    newElemList->neighbour = neighbour;
    if (head != NULL) {
        newElemList->next = this->head;
        this->head->prev = newElemList;
    }
    newElemList->prev = NULL;
    this->head = newElemList;

    size++;
}

ostream &operator<<(ostream &os, const List2 &a) {
    ElemList * p = a.head;
    while (p != NULL){
        os << p->neighbour << ":" << p->length << " ";
        p = p->next;
    }
    return os;
}

int List2::getSize() const{
    return this->size;
}

void List2::deleteElement(int value) {
    int position = this->findElement(value);
    if (position == -1) return;
    else if (position == 0){ //poczatek tabeli
        ElemList * p = this->head;
        this->head->next->prev = NULL;
        this->head = this->head->next;
        delete p;
    }
    else if (position == this->getSize()-1){ //koniec tabeli
        ElemList * p = this->head;
        while (p->next != NULL){
            p = p->next;
        }
        p->prev->next = NULL;
        delete p;
    }
    else {//inne miejsce tabeli
        int i = 0;
        ElemList * p = this->head;
        while (p != NULL && i < position){
            p = p->next;
            i++;
        }
        if (p != NULL){
            p->next->prev = p->prev;
            p->prev->next = p->next;
            delete p;
        }
    }
    size--;
}

int List2::findElement(int value) {
    int position = 0;
    ElemList * p = this->head;
    while (p != NULL){
        if (p->neighbour == value) {
            return position;
        }
        p = p->next;
        position++;
    }
    return -1;
}

void List2::menu() {
    cout << "MENU - lista\n"
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
            cout << "Prosze podac wartosc liczby do usuniecia.\n";
            int position;
            cin >> position;
            this->deleteElement(position);
            break;
        case 3:
            cout << "Prosze podac liczbe do wpisania.\n";
            cin >> position;
            cout << "Prosze podac liczbe, za ktora bedzie wpisana podana wczesniej wartosc.\n";
            int number;
            cin >> number;
            this->addElement(number,position);
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

void List2::print(std::ostream &str) const {
    str << *this;
}

int List2::getElement(int position) {
    ElemList * p = this->head;
    for (int i = 0; i < position && p != NULL; i++){
        p = p->next;
    }
    return p->length;
}

ElemList* List2::getPointerElement(int position){
    ElemList * p = this->head;
    for (int i = 0; i < position && p != NULL; i++){
        p = p->next;
    }
    return p;
}

ElemList *List2::getHead() const {
    return head;
}
