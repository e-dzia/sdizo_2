//
// Created by Edzia on 2017-03-06.
//

#include "List.h"

List::List() {
    this->head = NULL;
    size = 0;
}

List::~List() {
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

void List::loadFile(string name) {
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

void List::addElement(int afterValue, int value) {
    int position = this->findElement(afterValue);
    if (position == -1) position = 0;
    ElemList * newElemList = new ElemList();
    newElemList->length = value;
    if (position == 0){ //poczatek tabeli
        if (head != NULL) {
            newElemList->next = this->head;
            this->head->prev = newElemList;
        }
        newElemList->prev = NULL;
        this->head = newElemList;
    }
    else if (position >= this->getSize()-1){ //koniec tabeli
        ElemList * p = this->head;
        while (p->next != NULL){
            p = p->next;
        }
        newElemList->next = NULL;
        p->next = newElemList;
        newElemList->prev = p;
    }
    else {//inne miejsce tabeli
        int i = 0;
        ElemList * p = this->head;
        while (p != NULL && i < position){
            p = p->next;
            i++;
        }
        newElemList->next = p->next;
        p->next->prev = newElemList;
        p->next = newElemList;
        newElemList->prev = p;
    }
    size++;
}

ostream &operator<<(ostream &os, const List &a) {
    ElemList * p = a.head;
    while (p != NULL){
        os << p->length << " ";
        p = p->next;
    }
    return os;
}

int List::getSize() const{
    return this->size;
}

void List::deleteElement(int value) {
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

int List::findElement(int value) {
    int position = 0;
    ElemList * p = this->head;
    while (p != NULL){
        if (p->length == value) {
            return position;
        }
        p = p->next;
        position++;
    }
    return -1;
}

void List::menu() {
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

void List::print(std::ostream &str) const {
    str << *this;
}

int List::getElement(int position) {
    ElemList * p = this->head;
    for (int i = 0; i < position && p != NULL; i++){
        p = p->next;
    }
    return p->length;
}

ElemList *List::getHead() const {
    return head;
}
