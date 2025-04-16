#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo um tamanho máximo para a chave (nome, por exemplo)
#define TAM_CHAVE 50
#define N 100  // Tamanho total de objetos estimado

// Estrutura de um objeto a ser armazenado
typedef struct Objeto {
    char chave[TAM_CHAVE]; // Chave única para identificar o objeto
    int valor;             // Algum valor associado ao objeto
    struct Objeto* prox;   // Ponteiro para o próximo objeto na lista
} Objeto;

// Segundo nível: vetor de listas de objetos
typedef struct Lista {
    Objeto* inicio; // Ponteiro para o início da lista
} Lista;

// Primeiro nível: vetor de 10 ponteiros para vetores de listas
Lista** tabelaHash[10]; // Cada posição aponta para um vetor de listas

// Função hash do primeiro nível: mapeia a chave para uma das 10 tabelas
int hash1(char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % 10; // 10 posições no primeiro nível
}

// Função hash do segundo nível: mapeia a chave para uma das listas
int hash2(char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i] * (i + 1);
    }
    return soma % (N / 10); // Cada vetor secundário tem N/10 listas
}

// Inicializa a estrutura da tabela hash
void inicializarTabela() {
    for (int i = 0; i < 10; i++) {
        tabelaHash[i] = (Lista**) malloc((N / 10) * sizeof(Lista*));
        for (int j = 0; j < (N / 10); j++) {
            tabelaHash[i][j] = (Lista*) malloc(sizeof(Lista));
            tabelaHash[i][j]->inicio = NULL;
        }
    }
}

// Insere um novo objeto na tabela hash
void inserir(char* chave, int valor) {
    int indice1 = hash1(chave); // Primeiro nível
    int indice2 = hash2(chave); // Segundo nível

    // Criar novo objeto
    Objeto* novo = (Objeto*) malloc(sizeof(Objeto));
    strcpy(novo->chave, chave);
    novo->valor = valor;
    novo->prox = tabelaHash[indice1][indice2]->inicio;

    // Inserir no início da lista
    tabelaHash[indice1][indice2]->inicio = novo;
}

// Busca um objeto pela chave
Objeto* buscar(char* chave) {
    int indice1 = hash1(chave);
    int indice2 = hash2(chave);

    Objeto* atual = tabelaHash[indice1][indice2]->inicio;
    while (atual != NULL) {
        if (strcmp(atual->chave, chave) == 0) {
            return atual; // Encontrou o objeto
        }
        atual = atual->prox;
    }
    return NULL; // Não encontrado
}

// Função para imprimir todos os objetos (para teste)
void imprimirTudo() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < (N / 10); j++) {
            printf("Tabela[%d][%d]: ", i, j);
            Objeto* atual = tabelaHash[i][j]->inicio;
            while (atual != NULL) {
                printf("(%s, %d) -> ", atual->chave, atual->valor);
                atual = atual->prox;
            }
            printf("NULL\n");
        }
    }
}

// Função principal de teste
int main() {
    inicializarTabela();

    inserir("joao", 10);
    inserir("maria", 20);
    inserir("jose", 30);

    Objeto* resultado = buscar("maria");
    if (resultado != NULL) {
        printf("Objeto encontrado: %s, valor = %d\n", resultado->chave, resultado->valor);
    } else {
        printf("Objeto não encontrado\n");
    }

    imprimirTudo();

    return 0;
}
