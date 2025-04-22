#include <stdio.h>   // Biblioteca para funções de entrada e saída (printf, etc.)
#include <stdlib.h>  // Biblioteca para alocação dinâmica de memória (malloc, free)

struct no {              // Estrutura que representa um nó da lista encadeada
    int dado;            // Dado armazenado no nó
    struct no *prox;     // Ponteiro para o próximo nó da lista
};

// Função para criar uma lista vazia (retorna NULL)
struct no* criar_lista() {
    return NULL;
}

// Verifica se a lista está vazia (se o ponteiro é NULL)
char ehVazia(struct no* l) {
    return l == NULL;
}

// Retorna o número de elementos da lista
int tamanho(struct no* l) {
    int count = 0;               // Contador de nós
    while (l != NULL) {          // Percorre até o fim da lista
        count++;                 // Incrementa o contador
        l = l->prox;             // Avança para o próximo nó
    }
    return count;                // Retorna o número total de nós
}

// Retorna o valor contido em uma posição específica (pos inicia em 1)
int obter(struct no* l, int pos) {
    int i = 1;                   // Índice atual, começando de 1
    while (l != NULL) {          // Percorre a lista
        if (i == pos) return l->dado; // Se posição desejada, retorna o valor
        l = l->prox;             // Avança para o próximo nó
        i++;                     // Incrementa o índice
    }
    return -1;                   // Se posição inválida, retorna -1
}

// Modifica o valor de um elemento em uma posição específica
char modificar(struct no* l, int pos, int valor) {
    int i = 1;                   // Índice atual
    while (l != NULL) {          // Percorre a lista
        if (i == pos) {          // Se encontrou a posição
            l->dado = valor;     // Atualiza o valor do nó
            return 0;            // Retorna sucesso
        }
        l = l->prox;             // Avança para o próximo nó
        i++;                     // Incrementa o índice
    }
    return 1;                    // Retorna erro se posição inválida
}

// Insere um novo elemento em uma posição específica da lista
char inserir_posicao(struct no** l, int pos, int valor) {
    if (pos < 1 || pos > tamanho(*l) + 1) return 1; // Valida posição

    struct no* novo = (struct no*)malloc(sizeof(struct no)); // Aloca novo nó
    if (novo == NULL) return 1;                              // Verifica falha na alocação

    novo->dado = valor;             // Atribui valor ao novo nó
    if (pos == 1) {                 // Inserção no início
        novo->prox = *l;            // O próximo do novo nó aponta para o antigo início
        *l = novo;                  // Atualiza o início da lista
    } else {                        // Inserção no meio ou fim
        struct no* aux = *l;        // Ponteiro auxiliar
        for (int i = 1; i < pos - 1; i++) aux = aux->prox; // Vai até o nó anterior à posição
        novo->prox = aux->prox;     // Novo nó aponta para o próximo do anterior
        aux->prox = novo;           // Anterior aponta para o novo nó
    }
    return 0;                       // Sucesso
}

// Remove o elemento em uma posição específica da lista
char remover_posicao(struct no** l, int pos) {
    if (pos < 1 || pos > tamanho(*l)) return 1; // Verifica se posição é válida

    struct no* aux = *l, *ant = NULL;           // Ponteiros auxiliares
    if (pos == 1) {                             // Se for o primeiro elemento
        *l = aux->prox;                         // Início aponta para o segundo
        free(aux);                              // Libera o nó removido
    } else {
        for (int i = 1; i < pos; i++) {         // Percorre até a posição
            ant = aux;                          // Armazena o anterior
            aux = aux->prox;                    // Avança para o próximo
        }
        ant->prox = aux->prox;                  // O anterior aponta para o próximo do removido
        free(aux);                              // Libera memória do nó removido
    }
    return 0;                                   // Sucesso
}

// Imprime todos os elementos da lista
void mostrar(struct no* l) {
    if (ehVazia(l)) {                           // Verifica se a lista está vazia
        printf("Lista vazia\n");
        return;
    }
    while (l != NULL) {                         // Percorre e imprime os dados
        printf("%d -> ", l->dado);
        l = l->prox;
    }
    printf("NULL\n");                           // Final da lista
}

// Função principal de teste
int main() {
    struct no* lista = criar_lista();           // Cria uma nova lista

    printf("Testando inserção:\n");
    inserir_posicao(&lista, 1, 10);             // Insere no início
    inserir_posicao(&lista, 2, 20);             // Insere no final
    inserir_posicao(&lista, 3, 30);             // Insere no final
    inserir_posicao(&lista, 2, 15);             // Insere no meio (entre 10 e 20)
    mostrar(lista);                             // Mostra a lista

    printf("\nTestando modificação:\n");
    modificar(lista, 2, 25);                    // Altera valor da posição 2
    mostrar(lista);                             // Mostra lista modificada

    printf("\nTestando obtenção:\n");
    printf("Elemento na posição 3: %d\n", obter(lista, 3));    // Pega valor da posição 3
    printf("Elemento na posição 5 (inválido): %d\n", obter(lista, 5)); // Teste inválido

    printf("\nTestando remoção:\n");
    remover_posicao(&lista, 2);                 // Remove do meio
    mostrar(lista);
    remover_posicao(&lista, 1);                 // Remove do início
    mostrar(lista);
    remover_posicao(&lista, 2);                 // Remove do fim
    mostrar(lista);
    remover_posicao(&lista, 1);                 // Remove último elemento
    mostrar(lista);

    printf("\nTestando tamanho da lista:\n");
    printf("Tamanho da lista: %d\n", tamanho(lista)); // Mostra tamanho atual

    return 0;                                    // Fim do programa
}
