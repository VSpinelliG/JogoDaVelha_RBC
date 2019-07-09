#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream>
using namespace std;

typedef int Dado;

class noh {
friend class lista;
friend void dobraValor(noh* umNoh);
friend void triplicaValor(noh* umNoh);
private:
    Dado dado;
    noh* proximo;
public:
    noh(Dado d = 0);
};

class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
public:
    lista();
    ~lista();
    lista(const lista& l);
    void insere(Dado dado);
    void insereNoFim(Dado dado);
    void insereNoInicio(Dado dado);
    void insereNaPosicao(int posicao, Dado dado);
    void imprime();
    inline bool vazia();
    void percorre( void (*funcao) (noh* umNoh));
    void remove(int posicao);
    int procura(Dado valor);//retorna posicao
    void imprimeReverso(noh* umNoh);
    void imprimeReverso();
    noh* acessaPosicao(int posicao);
    void percorreReverso( void (*funcao) (noh* umNoh));
    bool operator==(const lista& l);
    lista& operator+(const lista& minhaLista);

};

#endif //LISTA_H
