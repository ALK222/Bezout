#include <iostream>
#include <cstdlib>
#include "TextTable.h"
using namespace std;

struct tBezout
{
    int a;
    int b;
    int r;
    int c;
    int m;
    int n;
};

struct tListaBezout
{
    tBezout* bezout;
    int contador;
};


void initialize(tListaBezout& list);

int calculo(tListaBezout& list);

void ampliar(tListaBezout& list, const int index);

void calculoMN(tListaBezout& list);

void createTable(TextTable& t, tListaBezout& list);


int main(int argc, char** argv) {
    TextTable t('-', '|', '+');
    tListaBezout list;
    list.bezout = new tBezout[1];
    initialize(list);
    list.bezout[0].a = atoi(argv[1]);
    list.bezout[0].b = atoi(argv[2]);
    calculo(list);
    calculoMN(list);
    createTable(t, list);
    delete[] list.bezout;
    return 0;
}

void initialize(tListaBezout& list) {
    list.contador = 1;
}

int calculo(tListaBezout& list) {
    int index = 0;
    while (list.bezout[index].b != 0) {
        list.bezout[index].c = list.bezout[index].a / list.bezout[index].b;
        list.bezout[index].r = list.bezout[index].a % list.bezout[index].b;
        ampliar(list, index);
        ++index;
        ++list.contador; 
    }
    list.bezout[list.contador - 1].c = 0;
    list.bezout[list.contador - 1].r = 0;
    return list.bezout[list.contador - 1].a;
}

void ampliar(tListaBezout& list, const int index) {
    tBezout* aux = new tBezout[list.contador + 1];
    for (int i = 0; i < list.contador; ++i) {
        aux[i] = list.bezout[i];
    }
    aux[list.contador].a = list.bezout[list.contador - 1].b;
    aux[list.contador].b = list.bezout[list.contador - 1].r;
    delete[] list.bezout;
    list.bezout = aux;
}

void calculoMN(tListaBezout& list) {
    list.bezout[list.contador - 1].m = 1;
    list.bezout[list.contador - 1].n = 0;
    for (int i = list.contador - 2; i >= 0; --i) {
        list.bezout[i].m = list.bezout[i + 1].n;
        list.bezout[i].n = list.bezout[i + 1].m - (list.bezout[i + 1].n * list.bezout[i].c);
    }
}

void createTable(TextTable& t, tListaBezout& list) {
    t.add("i");
    t.add("a");
    t.add("b");
    t.add("r");
    t.add("c");
    t.add("m");
    t.add("n");
    t.endOfRow();
    for (int j = 0; j < list.contador; ++j) {
        t.add(to_string(j));
        t.add(to_string(list.bezout[j].a));
        t.add(to_string(list.bezout[j].b));
        t.add(to_string(list.bezout[j].r));
        t.add(to_string(list.bezout[j].c));
        t.add(to_string(list.bezout[j].m));
        t.add(to_string(list.bezout[j].n));
        t.endOfRow();
    }
    t.setAlignment(2, TextTable::Alignment::RIGHT);
    cout << t;
}