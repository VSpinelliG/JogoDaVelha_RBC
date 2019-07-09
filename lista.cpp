#include <iostream>
#include "lista.hpp"
using namespace std;

noh:: noh(Dado d) {
    dado = d;
    proximo = NULL;
}

void dobraValor(noh* umNoh) {
    umNoh->dado *= 2;
}

void triplicaValor(noh* umNoh) {
    umNoh->dado *= 3;
}

//constroi uma lista inicialmente vazia
lista::lista() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

//destrutor
lista::~lista() {
    noh* aux = primeiro;
    noh* temp;

    while (aux != NULL) {
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    //nao é necessario, mas evita problemas
    primeiro = NULL;
    ultimo = NULL;
}

lista::lista(const lista& l) {
    noh* aux = l.primeiro;
    primeiro = NULL;
    ultimo = NULL;
    while (aux != NULL) {
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
}

void lista::insere(Dado dado) { //insere por padrao no fim
    insereNoFim(dado);
}

void lista::insereNoFim(Dado dado) {
    // * primeiro criamos o novo nó
    noh* novo = new noh(dado);

    // * agora inserimos o nó na lista
    // se a lista estiver vazia, inserimos no primeiro nó
    if ( vazia() ) { //ou (primeiro == NULL) ou (tamanho == 0)
        primeiro = novo;
        ultimo = novo;
    }
    else { // ja tem elemento na lista, insere no final
        ultimo->proximo = novo;
        ultimo = novo;
    }
    ++tamanho;
}

void lista::insereNoInicio(Dado dado) {
    noh* novo = new noh(dado);
    // * agora inserimos o nó na lista
    // se a lista estiver vazia, inserimos no primeiro no
    if ( vazia() ) { //ou (primeiro == NULL) ou (tamanho == 0)
        primeiro = novo;
        ultimo = novo;
    }
    else {
        novo->proximo = primeiro;
        primeiro = novo;
    }
    ++tamanho;
}

//insere em uma determinada posicao
void lista::insereNaPosicao(int posicao, Dado dado) {
    noh* novo = new noh(dado);

    // * agora inserimos o nó na lista
    // se a lista estiver vazia, inserimos no primeiro no
    if ((posicao <= tamanho) and (posicao >= 0)) {
        if ( vazia() ) { //ou (primeiro == NULL) ou (tamanho == 0)
            primeiro = novo;
            ultimo = novo;
        }
        else if (posicao == tamanho) { //insere no fim
            ultimo->proximo = novo;
            ultimo = novo;
        } else {
            noh* aux = primeiro;
            int posAux = 0;

            //chegando na posicao da lista
            while (posAux < (posicao-1)) {
                aux = aux->proximo;
                posAux++;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
        tamanho++;
    } else {
        //tratar excessao
    }
}

/*
void trocarCelula(int pos1, int pos2) {
    noh* aux1 = primeiro;
    int posAux1 = 0;
    while ((aux1 != NULL) and (posAux1 < pos1)) {
        aux1 = aux1->proximo;
        ++posAux1;
    }

    noh* aux2 = primeiro;
    int posAux2 = 0;
    while ((aux2 != NULL) and (posAux2 < pos2)) {
        aux2 = aux2->proximo;
        ++posAux1;
    }



}
*/
//metodo basico que percorre a lista, imprimindo seus elementos
void lista::imprime() {
    noh* aux = primeiro;
    while (aux != NULL) {
        cout << aux->dado << ' ';
        aux = aux->proximo;
    }
    cout << endl;
}

// verifica se a lista esta vazia
inline bool lista::vazia() {
    return (primeiro == NULL);
}

// percorre os nós da lista aplicando uma dada funcao
void lista::percorre( void (*funcao) (noh* umNoh)) {
    noh* aux = primeiro;
    while (aux != NULL) {
        funcao(aux);
        aux = aux->proximo;
    }
}

void lista::remove(int posicao) {
    //verifica antes se a posica existe
    if ((posicao <= tamanho) and (posicao >= 0)) {
        if (posicao == 0) {
            noh* aux = primeiro;
            primeiro = primeiro->proximo;
            delete aux;
        } else { //precisa percorrer para achar
            noh* aux = primeiro->proximo;
            noh* ant = primeiro;
            int posAux = 1;
            while ((aux != NULL) and (posAux < posicao)) {
                ant = aux;
                aux = aux->proximo;
                posAux++;
            }
            if (aux == ultimo) {
                ant->proximo = NULL;
                ultimo = ant;
                delete aux;
            } else {
                ant->proximo = aux->proximo;
                delete aux;
            }
        }
        tamanho--;
    } else {
        cout << "Posicao nao encontrada" << endl;
        //tratar o erro
    }
}

int lista::procura(Dado valor){ //retorna posicao
    noh* aux = primeiro;
    int posAux = 0;

    while ((aux != NULL) and (aux->dado != valor)) {
        posAux++;
        aux = aux->proximo;
    }
    if (aux == NULL) {
        posAux = -1;
    }
    return posAux;
}

void lista::imprimeReverso(noh* umNoh) { //funcao recursiva
    if (umNoh->proximo == NULL) {
        cout << umNoh->dado << ' ';
    } else {
        imprimeReverso(umNoh->proximo);
        cout << umNoh->dado << ' ';
    }
}

void lista::imprimeReverso() {
    imprimeReverso(primeiro);
}

noh* lista::acessaPosicao(int posicao) {
    noh* aux = primeiro;
    int posAux = 0;

    while ((aux != NULL) and (posAux < posicao)) {
        aux = aux->proximo;
        posAux++;
    }
    return aux;
}

void lista::percorreReverso( void (*funcao) (noh* umNoh)) {
}

bool lista::operator==(const lista& l) {
    if (l.tamanho != tamanho) {
        cout << __LINE__ << endl;
        return false;
    }
    else {
        noh* aux1 = primeiro;
        noh* aux2 = l.primeiro;
        while ((aux1 != NULL) and (aux2 != NULL)) {
            if (aux1->dado != aux2->dado) {
                cout << __LINE__ << endl;
                return false;
            }
            aux1 = aux1->proximo;
            aux2 = aux2->proximo;
        }
    }
    return true;
}


lista& lista::operator+(const lista& minhaLista){
    tamanho += minhaLista.tamanho;
    ultimo->proximo = minhaLista.primeiro;
    ultimo = minhaLista.ultimo;
    return *this;
}
