#include <stdio.h>
#include <stdlib.h>

struct no {
    int dado;
    struct no *prox;
};

// Criar lista vazia
struct no* criar_lista() {
    return NULL;
}

// Verificar se a lista está vazia
char ehVazia(struct no* l) {
    return l == NULL;
}

// Obter o tamanho da lista
int tamanho(struct no* l) {
    int count = 0;
    while (l != NULL) {
        count++;
        l = l->prox;
    }
    return count;
}

// Obter o valor em uma posição específica
int obter(struct no* l, int pos) {
    int i = 1;
    while (l != NULL) {
        if (i == pos) return l->dado;
        l = l->prox;
        i++;
    }
    return -1; 
}

// Modificar um elemento em uma posição específica
char modificar(struct no* l, int pos, int valor) {
    int i = 1;
    while (l != NULL) {
        if (i == pos) {
            l->dado = valor;
            return 0;
        }
        l = l->prox;
        i++;
    }
    return 1;
}

// Inserir um elemento em uma posição específica
char inserir_posicao(struct no** l, int pos, int valor) {
    if (pos < 1 || pos > tamanho(*l) + 1) return 1;

    struct no* novo = (struct no*)malloc(sizeof(struct no));
    if (novo == NULL) return 1;

    novo->dado = valor;
    if (pos == 1) {
        novo->prox = *l;
        *l = novo;
    } else {
        struct no* aux = *l;
        for (int i = 1; i < pos - 1; i++) aux = aux->prox;
        novo->prox = aux->prox;
        aux->prox = novo;
    }
    return 0;
}

// Remover um elemento de uma posição específica
char remover_posicao(struct no** l, int pos) {
    if (pos < 1 || pos > tamanho(*l)) return 1;

    struct no* aux = *l, *ant = NULL;
    if (pos == 1) {
        *l = aux->prox;
        free(aux);
    } else {
        for (int i = 1; i < pos; i++) {
            ant = aux;
            aux = aux->prox;
        }
        ant->prox = aux->prox;
        free(aux);
    }
    return 0;
}

// Mostrar a lista
void mostrar(struct no* l) {
    if (ehVazia(l)) {
        printf("Lista vazia\n");
        return;
    }
    while (l != NULL) {
        printf("%d -> ", l->dado);
        l = l->prox;
    }
    printf("NULL\n");
}

int main() {
    struct no* lista = criar_lista();

    printf("Testando inserção:\n");
    inserir_posicao(&lista, 1, 10);
    inserir_posicao(&lista, 2, 20);
    inserir_posicao(&lista, 3, 30);
    inserir_posicao(&lista, 2, 15); // Inserir no meio
    mostrar(lista);

    printf("\nTestando modificação:\n");
    modificar(lista, 2, 25);
    mostrar(lista);

    printf("\nTestando obtenção:\n");
    printf("Elemento na posição 3: %d\n", obter(lista, 3));
    printf("Elemento na posição 5 (inválido): %d\n", obter(lista, 5));

    printf("\nTestando remoção:\n");
    remover_posicao(&lista, 2); // Remover do meio
    mostrar(lista);
    remover_posicao(&lista, 1); // Remover do início
    mostrar(lista);
    remover_posicao(&lista, 2); // Remover do fim
    mostrar(lista);
    remover_posicao(&lista, 1); // Remover único elemento
    mostrar(lista);

    printf("\nTestando tamanho da lista:\n");
    printf("Tamanho da lista: %d\n", tamanho(lista));

    return 0;
}
