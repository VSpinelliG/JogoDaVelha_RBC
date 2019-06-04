#include <iostream>
#include <list>
#include "Jogada.hpp"
#include <cstdlib>

using namespace std;

int* retornaVetor(){
    int vetor[] = {0,1,2,3,4,5,6,7,8};
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
    Movimento** tabuleiro = new Movimento*[3];
    for(int lin = 0; lin < 3; lin++) {
        tabuleiro[lin] = new Movimento[3];
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
                bool jogoEmAndamento = false;
                char jogador1 = 'X';
                char jogador2 = 'O';
                int jogadorInicial = rand() % 2 + 1;
                //cout << jogadorInicial << endl;
                if (jogadorInicial == 2) swap(jogador1, jogador2);
                int* vetor = retornaVetor();
                for (int i = 0; i < 9; i++) {
                    cout << vetor[i] << " ";
                    
                }
                
                while(jogoEmAndamento){
                    
                    
                }
                ++i;
            }
            break;
    }

    return 0;
}
