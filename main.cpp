#include <iostream>
#include "hash.cpp"
#include <cstdlib>
#include <time.h>
using namespace std;

ostream& operator<<(ostream& output, const char** tabuleiro) {
    for (int k = 0; k < 3; ++k){
        for (int j = 0; j < 3; ++j){
            output << tabuleiro[k][j] << " ";
        }
        output << endl;
    }
    output << endl;
    return output;
}

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
    srand(time(NULL));
    int *vetor = new int[9];
    for (int i = 0; i < 9; i++) vetor[i] = i;
    for (int i = 0; i < 9; i++) {
        int r = rand() % 9;
        swap(vetor[r], vetor[i]);
    }
    for (int i = 0; i < 9; i++) cout << vetor[i] << ' ';
    cout << endl;
    return vetor;
}

char** novoTabuleiro(){
    char** tabuleiro = new char*[3];
    for(int lin = 0; lin < 3; lin++) {
        tabuleiro[lin] = new char[3];
    }
    
    for (int lin = 0; lin < 3; lin++) {
        for (int col = 0; col < 3; col++) {
            tabuleiro[lin][col] = '-';
        }
    }
    
    return tabuleiro;
}

int main() {

    tabelaHash minhaHash;
    minhaHash.carregarDadosArquivo();
    //minhaHash.percorre();

    int tipoJogo;
    cout << "0 - Jogador contra Jogador" << endl;
    cout << "1 - Jogador contra Maquina" << endl;
    cout << "2 - Maquina contra Maquina (Treino)" << endl;
    cout << "9 - Sair" << endl;
    cout << "Selecione o modo de jogo: ";
    cin >> tipoJogo;

    /*
    //Criando o tabuleiro
    char** tabuleiro = new char*[3];
    for(int lin = 0; lin < 3; lin++) {
        tabuleiro[lin] = new char[3];
    }
    */
    while(tipoJogo != 9) {
        switch(tipoJogo) {
            case 0:
                {     
                    // Jogador contra jogador
                    bool jogo_em_andamento = true;
                    char jogador1 = 'X';
                    char jogador2 = 'O';
                    int linha, coluna;
                    srand(time(NULL));
                    if ((rand() % 2 + 1) == 2) swap(jogador1, jogador2);
                    cout << "O jogador \'" << jogador1 << "\' irá começar!" << endl;

                    // Inicializando o tabuleiro
                    char** tabuleiro = novoTabuleiro();

                    // Vetor que armazena informações dos movimentos
                    Movimento* movimentos = new Movimento[9];

                    // Controla o numero da jogada
                    int nJogada = 0;
                    while(jogo_em_andamento){
                        cout << tabuleiro << endl;
                        cout << "Jogador \'" << jogador1 << "\', digite o movimento [linha] [coluna]: ";
                        cin >> linha >> coluna;
                        tabuleiro[linha][coluna] = jogador1;

                        movimentos[nJogada].jogador = jogador1;
                        movimentos[nJogada].linha = linha;
                        movimentos[nJogada].coluna = coluna;

                        if (verificaGanhador(jogador1, tabuleiro) == jogador1){
                            cout << "Jogador \'" << jogador1 << "\' venceu!" << endl;
                            jogo_em_andamento = false;
                        }
                        else if(verificaGanhador(jogador1, tabuleiro) == 'v' and nJogada == 8){
                            jogo_em_andamento = false;
                            cout << "Deu velha :(" << endl;
                        }
                        else{
                            system("clear");
                            swap(jogador1, jogador2);
                            ++nJogada;
                        }
                    }
                    // Desalocando o tabuleiro
                    for (int v = 0; v < 3; v++) {
                        delete[] tabuleiro[v];
                    }                
                    delete[] tabuleiro; 
                }
                break;
            case 1:
                {
                    // Jogador contra Maquina
                    bool jogo_em_andamento = true;
                    char jogador1 = 'C';
                    char jogador2 = 'U';
                    int linha, coluna;

                    srand(time(NULL));
                    if ((rand() % 2 + 1) == 2) swap(jogador1, jogador2);
                    cout << "O jogador \'" << jogador1 << "\' irá começar!" << endl << endl;;

                    // Inicializando o tabuleiro
                    char** tabuleiro = novoTabuleiro();

                    // Vetor que armazena informações dos movimentos
                    Movimento* movimentos = new Movimento[9];

                    // Controla o numero da jogada
                    int nJogada = 0;

                    for (int k = 0; k < 3; ++k){
                        for (int j = 0; j < 3; ++j){
                            cout << tabuleiro[k][j] << " ";
                        }
                        cout << endl;
                    }
                    cout << endl;

                    while(jogo_em_andamento){

                        if(jogador1 == 'U'){
                            // Vez do computador jogar
                            cout << "Jogador \'" << jogador1 << "\', digite o movimento [linha] [coluna]: ";
                            cin >> linha >> coluna;

                            cout << endl;

                            tabuleiro[linha][coluna] = jogador1;

                            movimentos[nJogada].jogador = jogador1;
                            movimentos[nJogada].linha = linha;
                            movimentos[nJogada].coluna = coluna;

                        } else if(jogador1 == 'C') {
                            // Vez do usuario jogar
                            int pos = minhaHash.obterProximoMovimento(movimentos, nJogada);
                            if(pos == -1) pos = minhaHash.gerarMovimentoAleatorio(tabuleiro);
                            linha = retornaLinha(pos);
                            coluna = retornaColuna(pos);
                            tabuleiro[linha][coluna] = jogador1;

                            movimentos[nJogada].jogador = jogador1;
                            movimentos[nJogada].linha = linha;
                            movimentos[nJogada].coluna = coluna;
                        }

                        // Verifica se alguem ganhou
                        if (verificaGanhador(jogador1, tabuleiro) == jogador1){
                            cout << "Jogador \'" << jogador1 << "\' venceu!" << endl << endl;;
                            jogo_em_andamento = false;
                            // Se foi o computador que ganhou, armazena a jogada
                            if(jogador1 == 'C') minhaHash.insere(movimentos, jogador1);                            
                        }
                        else if(verificaGanhador(jogador1, tabuleiro) == 'v' and nJogada == 8){
                            jogo_em_andamento = false;
                            cout << "Deu velha :(" << endl;
                        }
                        else{
                            //system("clear");
                            swap(jogador1, jogador2);
                            ++nJogada;
                        }

                        for (int k = 0; k < 3; ++k){
                            for (int j = 0; j < 3; ++j){
                                cout << tabuleiro[k][j] << " ";
                            }
                            cout << endl;
                        }
                        cout << endl;
                    }
                    delete[] movimentos;
                    
                    // Desalocando o tabuleiro
                    for (int v = 0; v < 3; v++) {
                        delete[] tabuleiro[v];
                    }                
                    delete[] tabuleiro;   
                }            

                break;
            case 2:
                {
                    //Maquina contra maquina
                    int qtdJogos;
                    cout << "Digite a quantidade de jogos que a máquina jogará contra a máquina: ";
                    cin >> qtdJogos;
                    int i = 0;
                    
                    while(i < qtdJogos) {
                        
                        char** tabuleiro = novoTabuleiro();
                        
                        bool jogo_em_andamento = true;
                        char jogador1 = 'X';
                        char jogador2 = 'O';
                        int jogadorInicial = rand() % 2 + 1;
                        srand(time(NULL));
                        //cout << jogadorInicial << endl;
                        if (jogadorInicial == 2) swap(jogador1, jogador2);                
                        
                        cout << "O jogador \'" << jogador1 << "\' irá começar!" << endl;
                        
                        int* vetor = retornaVetor();
                        Movimento* movimentos = new Movimento[9];
                        int nJogada = 0;
                        int linha = 0;
                        int coluna = 0;
                        
                        while(jogo_em_andamento) {
                            linha = retornaLinha(vetor[nJogada]);
                            coluna = retornaColuna(vetor[nJogada]);
                            //cout << linha << " " << coluna << " " << vetor[nJogada] << " " << nJogada << endl;
                            
                            movimentos[nJogada].jogador = jogador1;
                            movimentos[nJogada].linha = linha;
                            movimentos[nJogada].coluna = coluna;
                            
                            tabuleiro[linha][coluna] = jogador1;
                            
                            if (verificaGanhador(jogador1, tabuleiro) == jogador1){
                                cout << "Jogador \'" << jogador1 << "\' venceu!" << endl;
                                jogo_em_andamento = false;
                            }
                            else if(verificaGanhador(jogador1, tabuleiro) == 'v' and nJogada == 8){
                                jogo_em_andamento = false;
                                cout << "Deu velha :(" << endl;
                            }
                            else{
                                swap(jogador1, jogador2);
                                ++nJogada;
                            }
                        }                    
                        minhaHash.insere(movimentos, jogador1);
                        ++i;
                        
                        delete[] movimentos;
                        delete[] vetor;
                        
                        for (int k = 0; k < 3; ++k){
                            for (int j = 0; j < 3; ++j){
                                cout << tabuleiro[k][j] << " ";
                            }
                            cout << endl;
                        }
                    
                        // Desalocando o tabuleiro
                        for (int v = 0; v < 3; v++) {
                            delete[] tabuleiro[v];
                        }                
                        delete[] tabuleiro;                
                    }
                }
                break;
        }
        cout << endl << endl;
        cout << "0 - Jogador contra Jogador" << endl;
        cout << "1 - Jogador contra Maquina" << endl;
        cout << "2 - Maquina contra Maquina (Treino)" << endl;
        cout << "9 - Sair" << endl;
        cout << "Selecione o modo de jogo: ";
        cin >> tipoJogo;
        cout << endl;
    }

    minhaHash.percorre();
    minhaHash.gravarDadosArquivo();
    
    return 0;
}
