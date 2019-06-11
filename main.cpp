#include <iostream>
#include <list>
#include "Jogada.hpp"
#include <cstdlib>

using namespace std;

char verificaGanhador(char jogador, char** tabuleiro){
    if (tabuleiro[0][0] == jogador and tabuleiro[0][1] == jogador and tabuleiro[0][2] == jogador){
        return jogador;
    }
    if (tabuleiro[1][0] == jogador and tabuleiro[1][1] == jogador and tabuleiro[1][2] == jogador){
        return jogador;
    }
    if (tabuleiro[2][0] == jogador and tabuleiro[2][1] == jogador and tabuleiro[2][2] == jogador){
        return jogador;
    }
    if (tabuleiro[0][0] == jogador and tabuleiro[1][0] == jogador and tabuleiro[2][0] == jogador){
        return jogador;
    }
    if (tabuleiro[0][1] == jogador and tabuleiro[1][1] == jogador and tabuleiro[2][1] == jogador){
        return jogador;
    }
    if (tabuleiro[0][2] == jogador and tabuleiro[1][2] == jogador and tabuleiro[2][2] == jogador){
        return jogador;
    }
    if (tabuleiro[0][0] == jogador and tabuleiro[1][1] == jogador and tabuleiro[2][2] == jogador){
        return jogador;
    }
    if (tabuleiro[0][2] == jogador and tabuleiro[1][1] == jogador and tabuleiro[2][0] == jogador){
        return jogador;
    }
    return 'v';
}

int retornaLinha(int l){
    if (l >= 0 and l < 3) return 0;
    else if (l >= 3 and l < 6) return 1;
    else return 2;
}

int retornaColuna(int c){
    if (c == 0 or c == 3 or c == 6) return 0;
    else if (c == 1 or c == 4 or c == 7) return 1;
    else return 2;
}

int* retornaVetor(){
    int *vetor = new int[9];
    for (int i = 0; i < 9; i++) vetor[i] = i;
    for (int i = 0; i < 9; i++) {
        int r = rand() % 9;
        swap(vetor[r], vetor[i]);
    }
    
    return vetor;
}

int main() {
    int tipoJogo;
    cout << "0 - Jogador contra Jogador" << endl;
    cout << "1 - Jogador contra Maquina" << endl;
    cout << "2 - Maquina contra Maquina (Treino)" << endl;
    cout << "Selecione o modo de jogo: ";
    cin >> tipoJogo;
    
    //Criando o tabuleiro
    char** tabuleiro = new char*[3];
    for(int lin = 0; lin < 3; lin++) {
        tabuleiro[lin] = new char[3];
    }
    
    switch(tipoJogo) {
        case 0:
            // Jogador contra jogador
            break;
        case 1:
            // Jogador contra Maquina
            break;
        case 2:
            //Maquina contra maquina
            int qtdJogos;
            cout << "Digite a quantidade de jogos que a máquina jogará contra a máquina: ";
            cin >> qtdJogos;
            int i = 0;
            
            while(i < qtdJogos) {
                bool jogoEmAndamento = true;
                char jogador1 = 'X';
                char jogador2 = 'O';
                int jogadorInicial = rand() % 2 + 1;
                //cout << jogadorInicial << endl;
                if (jogadorInicial == 2) swap(jogador1, jogador2);
                
                int* vetor = retornaVetor();
                Movimento* movimentos = new Movimento[9];
                int nJogada = 0;
                int linha = 0;
                int coluna = 0;
                
                while(jogoEmAndamento){
                    linha = retornaLinha(vetor[nJogada]);
                    coluna = retornaColuna(vetor[nJogada]);
                    cout << linha << " " << coluna << endl;
                    movimentos[nJogada].jogador = jogador1;
                    movimentos[nJogada].linha = linha;
                    movimentos[nJogada].coluna = coluna;
                    tabuleiro[linha][coluna] = jogador1;
                    if (verificaGanhador(jogador1, tabuleiro) == jogador1){
                        cout << "Jogador 1 venceu!" << endl;
                        jogoEmAndamento = false;
                    }
                    else{
                        swap(jogador1, jogador2);
                        ++nJogada;
                    }
                }
                ++i;
                delete[] movimentos;
                
                for (int k = 0; k < 3; ++k){
                    for (int j = 0; j < 3; ++j){
                        cout << tabuleiro[k][j] << " ";
                    }
                    cout << endl;
                }
            }
            break;
    }
    

    return 0;
}
