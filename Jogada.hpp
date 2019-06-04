#ifndef JOGADA_HPP
#define JOGADA_HPP

using namespace std;

typedef struct {
    int posJogada;
    char jogador;
} Movimento;

class Jogada {
    public:
        // Vetor de 9 posições, as posições são as seguintes
        /*
         *  0 | 1 | 2
         * ---+---+---
         *  3 | 4 | 5
         * ---+---+---
         *  6 | 7 | 8
         */ 
        Movimento* jogadas;
        char vencedor;
        int nVitorias;
    private:
        Jogada(Movimento* jogadas);
        ~Jogada();
};

#endif

