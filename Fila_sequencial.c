#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    int dados[MAX];
    int frente, tras, tamanho;
} Fila;

//Criar uma fila vazia
void criarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

//Testar se a fila está vazia
int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

//Verificar se a fila está cheia
int filaCheia(Fila *f) {
    return f->tamanho == MAX;
}

//Obter o tamanho da fila
int tamanhoFila(Fila *f) {
    return f->tamanho;
}

//Consultar o elemento da frente da fila
int frenteFila(Fila *f, int *elemento) {
    if (filaVazia(f)) {
        return 0; // Fila vazia
    }
    *elemento = f->dados[f->frente];
    return 1;
}

//Inserir um novo elemento no fundo da fila
int enfileirar(Fila *f, int valor) {
    if (filaCheia(f)) {
        return 0; // Fila cheia
    }
    f->tras = (f->tras + 1) % MAX;
    f->dados[f->tras] = valor;
    f->tamanho++;
    return 1;
}

//Remover o elemento da frente da fila
int desenfileirar(Fila *f, int *valor) {
    if (filaVazia(f)) {
        return 0; // Fila vazia
    }
    *valor = f->dados[f->frente];
    f->frente = (f->frente + 1) % MAX;
    f->tamanho--;
    return 1;
}

//Função para exibir a fila
void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Fila: ");
    for (int i = 0, idx = f->frente; i < f->tamanho; i++, idx = (idx + 1) % MAX) {
        printf("%d ", f->dados[idx]);
    }
    printf("\n");
}

int main() {
    Fila fila;
    criarFila(&fila);
    int elemento;

    //Inserção
    enfileirar(&fila, 10);
    enfileirar(&fila, 20);
    enfileirar(&fila, 30);
    enfileirar(&fila, 40);
    enfileirar(&fila, 50);
    exibirFila(&fila);
    
    //Tentativa de enfileirar em fila cheia
    if (!enfileirar(&fila, 60)) {
        printf("Fila cheia, não foi possível inserir 60.\n");
    }

    //Removendo elementos
    desenfileirar(&fila, &elemento);
    printf("Elemento removido: %d\n", elemento);
    desenfileirar(&fila, &elemento);
    printf("Elemento removido: %d\n", elemento);
    exibirFila(&fila);
    
    enfileirar(&fila, 60);
    puts("Elemento adicionado: ");
    exibirFila(&fila);

    //Consulta ao primeiro elemento
    if (frenteFila(&fila, &elemento)) {
        printf("Elemento da frente: %d\n", elemento);
    }

    return 0;
}