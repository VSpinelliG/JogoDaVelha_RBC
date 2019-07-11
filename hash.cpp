#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;


typedef struct {
    char jogador = '-';
    int linha = -1;
    int coluna = -1;
} Movimento;


class noh {
friend class tabelaHash;
friend inline bool operator==(const noh& noh1, const noh& noh2);
    private:
        /* Vetor de 9 posições, as posições são as seguintes
        *  0 | 1 | 2
        * ---+---+---
        *  3 | 4 | 5
        * ---+---+---
        *  6 | 7 | 8
        */ 
        Movimento* movimento;
        char vencedor;
        int nVitorias;
        noh* proximo;
    public:
        noh(Movimento* m, char winner, int vitorias = 0) {
            // for (int i = 0; i < 9; i++) {
            //     cout << m[i].linha << "*" << m[i].coluna << endl;
            // }
            movimento = new Movimento[9];
            for (int i = 0; i < 9; i++) movimento[i] = m[i];
            vencedor = winner;
            nVitorias = vitorias;
            proximo = NULL;
        }
        ~noh(){
            delete[] movimento;
            proximo = NULL;
        }
};

// Sobrecarga de operadores
inline bool operator==(const noh& noh1, const noh& noh2){
    for (int i = 0; i < 9; i++) {
        if(noh1.movimento[i].coluna != noh2.movimento[i].coluna) return false;
        else if(noh1.movimento[i].linha != noh2.movimento[i].linha) return false;
        else if(noh1.movimento[i].jogador != noh2.movimento[i].jogador) return false;
    }    
    return true;
}

inline int funcaoHash(Movimento* m) {
    return m[0].linha*3 + m[0].coluna;    
}

class tabelaHash {
private:
    //vetor de ponteiro de no
    noh** elementos;
    int capacidade;
public:
    tabelaHash(int cap = 9) {
        elementos = new noh*[cap];
        capacidade = cap;

        for (int i = 0; i < cap; i++) {
            elementos[i] = NULL;
        }
    }

    ~tabelaHash() {
        for (int i = 0; i < capacidade; i++) {
            noh* atual = elementos[i];

            //percorre a lista removendo todos os nos
            while (atual != NULL) {
                noh* aux = atual;
                atual = atual->proximo;
                delete aux;
            }
        }
        delete[] elementos;
    }

    //insere um valor v com chave c
    void insere(Movimento* m, char winner, int vitorias = 0) {
        //cout << "Inserindo no hash" << endl;
        // Encontrando a posição para inserir
        int h;
        h = funcaoHash(m);       

        if (recupera(m) == "NAO ENCONTRADO!") {
            if (elementos[h] == NULL) {
                elementos[h] = new noh(m, winner, vitorias);
            }
            else {
                //cout << "colidiu" << endl;
                noh* atual = elementos[h];

                //achando local para inserção
                while (atual->proximo != NULL) {
                    atual = atual->proximo;
                }

                noh* novo = new noh(m, winner);
                atual->proximo = novo;
            }
        } else if(recupera(m) == "JA ESTA NO HASH") {
            altera(m);
        }
        else {
            cout << "Item ja esta na tabela2" << endl;
        }
    }

    //recupera um valor associado a uma chave
    string recupera(Movimento* m) {
        int h;
        h = funcaoHash(m);
        
        if ((elementos[h] != NULL) and (elementos[h]->movimento == m)) {
			for (int i = 0; i < 9; i++) {
				cout << elementos[h]->movimento[i].linha << " " << elementos[h]->movimento[i].coluna << endl;
			}
            return "JA ESTA NO HASH";
        }
        else {
            noh* atual = elementos[h];

            while ((atual != NULL) and !(atual->movimento == m)) {
                atual = atual->proximo;
            }

            if ((atual != NULL) and (atual->movimento == m)) {
                return "JA ESTA NO HASH";
            }
            else {
                return "NAO ENCONTRADO!";
            }
        }
    }

    //altera um valor associado a uma chave, basicamente incrementa o numero de vitorias
    void altera(Movimento* m) {
        //nao trata colisao e nem chave nao encontrada
        int h;
        h = funcaoHash(m);

        if(recupera(m) == "JA ESTA NO HASH"){
			
            if ((elementos[h] != NULL) and (elementos[h]->movimento == m)) {
                elementos[h]->nVitorias += 1;
            }
            else {
                noh* atual = elementos[h];

                while ((atual != NULL) and !(atual->movimento != m)) {
                    atual = atual->proximo;
                }

                if ((atual != NULL) and (atual->movimento == m)) {
                    atual->nVitorias += 1;
                }
                else {
                    cerr << "ERRO NA ALTERACAO!" << endl;
                }
            }
        } else {
            cerr << "O jogo não está armazenado" << endl;
        }
    }

    int gerarMovimentoAleatorio(char** tabuleiro){
        int* posicoes_disponiveis = new int[9];
        int quantidade_disponivel = 0;
        // Verifica todas as posições disponíveis e adiciona elas em um vetor
        for (int lin = 0; lin < 3; lin++) {
            for (int col = 0; col < 3; col++){
                if(tabuleiro[lin][col] == '-') {
                    posicoes_disponiveis[quantidade_disponivel] = lin*3 + col;
                    quantidade_disponivel++;
                }
            }
        }
        srand(time(NULL));
        // Pega um indice aleatorio e retorna a posição atribuida a ele
        int retorno = posicoes_disponiveis[rand() % quantidade_disponivel];
        delete[] posicoes_disponiveis;

        return retorno;
        
    }

    int obterProximoMovimento(Movimento* m, int numero_da_jogada){
        int h;
        h = funcaoHash(m);
        noh* atual = elementos[h];
        if(atual != NULL) { 
            while(atual != NULL) {
                // Procurar jogada idêntica
                bool jogada_ainda_serve = true;
                // Verificando até a posição da jogada atual se é igual a jogada armazenada
                for (int i = 0; i < numero_da_jogada and jogada_ainda_serve; i++) {
                    if((m[i].linha != atual->movimento[i].linha) or (m[i].coluna != atual->movimento[i].coluna)){
                        jogada_ainda_serve = false;
                    }
                }
                if(jogada_ainda_serve and (atual->movimento[numero_da_jogada].jogador == atual->vencedor)){
                    cout << "Encontrei uma jogada :)" << endl << endl;
                    return atual->movimento[numero_da_jogada].linha * 3 + atual->movimento[numero_da_jogada].coluna;
                }
                atual = atual->proximo;
            }
            // Se chegar aqui, gerar aleatorio também, não encontrou jogada igual
            cout << "Não encontrei uma jogada, vou gerar aleatorio :|" << endl << endl;
            return -1;
        } else {
            cout << "Não encontrei uma jogada, vou gerar aleatorio :|" << endl << endl;
            return -1;
            // Não tem jogo em que o primeiro movimento é nesta posição, necessário gerar aleatorio
        }
    }
    /*
    //retira um valor associado a uma chave
    void remove(string c) {
        int h;
        h = funcaoHash(c, capacidade);

        if ((elementos[h] != NULL) and (elementos[h]->chave == c)) {
            //removendo a cabeca da lista
            noh* aux = elementos[h];
            elementos[h] = elementos[h]->proximo;
            delete aux;
        }
        else {
            noh* atual = elementos[h];
            noh* anterior;

            while ((atual != NULL) and (atual->chave != c)) {
                anterior = atual;
                atual = atual->proximo;
            }

            if ((atual != NULL) and (atual->chave == c)) {
                anterio->proximo = atual->proximo;
                delete atual;
            }
            else {
                cerr << "ERRO NA REMOCAO" << endl;
            }
        }
    }
    */
    //percorrendo a tabela hash (para fins de debug)
    void percorre() {
        cout << "Imprimindo..." << endl;
        noh* atual;
        for (int i = 0; i < capacidade; i++) {
            cout << i << ": ";
            atual = elementos[i];
            
            while (atual != NULL) {
                cout << "[";
                for (int i = 0; i < 9; i++) cout << "(" << atual->movimento[i].linha << " " << atual->movimento[i].coluna << " " << atual->movimento[i].jogador << ")";
                cout << "/" << atual->vencedor << "/" << atual->nVitorias << "]->";
                atual = atual->proximo;
            }
            cout << "NULL" << endl;
        }
    }

    void carregarDadosArquivo(){
        // Abrindo o arquivo binario em modo leitura
		ifstream myFile("jogos.bin", ios::in | ios::binary);
		//system("clear");

        // Se o arquivo existe e foi aberto, leia os dados
		if(myFile){
			cout << "Procurando jogos em arquivo." << endl;
            // Verificando quantos jogos estão armazenados
			myFile.seekg(0, ios::end); // Posicionando o ponteiro no fim do arquivo
            long nJogos = myFile.tellg()/((sizeof(Movimento)*9) + sizeof(char) + sizeof(int));
            cout << "Encontramos " << nJogos << " jogos armazenados" << endl;
            
            // Posicionando o ponteiro de leitura no inicio do arquivo para começar a ler
            myFile.seekg(0); 
			Movimento* movimentos = new Movimento[9];
			char winner;
            int nVitorias = 0;

            // Para cada jogo no arquivo
			for(int i = 0; i < nJogos; i++){
                // Lendo cada movimento do jogo
                for (int j = 0; j < 9; j++) {
                    myFile.read(reinterpret_cast<char*>(&(movimentos[j])), sizeof(Movimento));
                }                            
				myFile.read(reinterpret_cast<char*>(&winner), sizeof(char));
                myFile.read(reinterpret_cast<char*>(&(nVitorias)), sizeof(int));

                // Inserindo o jogo lido na hash
				insere(movimentos, winner, nVitorias);
                // cout << "Winner " << winner << endl;
			}
			myFile.close();
		}
		else{
			cout << "Falha ao abrir o arquivo ou arquivo nao encontrado." << endl << endl;
		}
    }

    void gravarDadosArquivo(){
        // Abrindo o arquivo em modo escrita, apagando todo o conteudo que já existia
        ofstream myFile("jogos.bin", ios::trunc | ios::out | ios::binary);

        // Verificando se o arquivo foi aberto
        if(myFile) cout << "Arquivo criado com sucesso!" << endl;
        else cout << "Erro ao salvar as jogadas" << endl;

        // Posicionando o ponteiro de escrita no inicio do arquivo
		myFile.seekp(0);
		
        // Percorre em todas as posições do Hash
        for (int i = 0; i < capacidade; i++) {
            noh* atual = elementos[i];
            if(atual != NULL) {
                //Grava no arquivo
                while(atual != NULL) {
                    for(int j = 0; j < 9; j++){
                        // cout << "Nova linha: " << atual->movimento[j].linha << " "  << atual->movimento[j].coluna << endl;
                        myFile.write(reinterpret_cast<char*>(&(atual->movimento[j])), sizeof(Movimento));
                    }
                    myFile.write(reinterpret_cast<char*>(&(atual->vencedor)), sizeof(char));
                    myFile.write(reinterpret_cast<char*>(&(atual->nVitorias)), sizeof(int));

                    atual = atual->proximo;                  
                }
            }
        }
        cout << "Cada jogo no arquivo ocupa cerca de " << sizeof(Movimento)*9 + sizeof(char) + sizeof(int) << " bytes." << endl;
        
		myFile.close();
    }
};
