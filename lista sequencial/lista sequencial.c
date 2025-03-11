#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Tamanho máximo da lista

typedef struct {
    int dados[MAX];
    int tamanho;
} Lista;

// Função para criar uma lista vazia
void criarLista(Lista *lista) {
    lista->tamanho = 0;
}

// Função para verificar se a lista está vazia
int listaVazia(Lista *lista) {
    return lista->tamanho == 0;
}

// Função para verificar se a lista está cheia
int listaCheia(Lista *lista) {
    return lista->tamanho == MAX;
}

// Função para imprimir a lista
void imprimeLista(Lista *lista) {
    if (listaVazia(lista)) {
        printf("Lista vazia!\n");
        return;
    }
    for (int i = 0; i < lista->tamanho; i++) {
        printf("%d ", lista->dados[i]);
    }
    printf("\n");
}

// Função para obter o tamanho da lista
int obterTamanho(Lista *lista) {
    return lista->tamanho;
}

// Função para obter/modificar o valor do elemento de uma determinada posição
int obterElemento(Lista *lista, int pos) {
    if (pos < 1 || pos > lista->tamanho) {
        printf("Posição inválida!\n");
        return -1; 
    }
    return lista->dados[pos - 1]; 
}

void modificarElemento(Lista *lista, int pos, int valor) {
    if (pos < 1 || pos > lista->tamanho) {
        printf("Posição inválida!\n");
        return;
    }
    lista->dados[pos - 1] = valor; 
}

// Função para inserir um elemento em uma determinada posição
void inserirElemento(Lista *lista, int pos, int valor) {
    if (listaCheia(lista)) {
        printf("Lista cheia!\n");
        return;
    }
    if (pos < 1 || pos > lista->tamanho + 1) {
        printf("Posição inválida!\n");
        return;
    }
    for (int i = lista->tamanho; i >= pos; i--) {
        lista->dados[i] = lista->dados[i - 1]; 
    }
    lista->dados[pos - 1] = valor; 
    lista->tamanho++;
}

// Função para retirar um elemento de uma determinada posição
void retirarElemento(Lista *lista, int pos) {
    if (listaVazia(lista)) {
        printf("Lista vazia!\n");
        return;
    }
    if (pos < 1 || pos > lista->tamanho) {
        printf("Posição inválida!\n");
        return;
    }
    for (int i = pos; i < lista->tamanho; i++) {
        lista->dados[i - 1] = lista->dados[i]; 
    }
    lista->tamanho--;
}

// Função principal para testar a lista
int main() {
    printf("\n\nTeste estático\n\n");
    Lista lista;
    criarLista(&lista);
    
    imprimeLista(&lista);
    inserirElemento(&lista, 1, 10);
    inserirElemento(&lista, 2, 20);
    inserirElemento(&lista, 3, 30);
    
    printf("Elementos adicionados a lista: ");
    imprimeLista(&lista);

    printf("Tamanho da lista: %d\n", obterTamanho(&lista));
    printf("Elemento na posição 2: %d\n", obterElemento(&lista, 2));
    
    printf("Modificando posiçao 2 por 25...\n");
    modificarElemento(&lista, 2, 25);
    printf("Elemento na posição 2 após modificação: %d\n", obterElemento(&lista, 2));
    
    printf("Removendo elemento da posição 1...\n");
    retirarElemento(&lista, 1);
    printf("Tamanho da lista após remoção: %d\n", obterTamanho(&lista));
    
    printf("Lista Final: ");
    imprimeLista(&lista);
    
    printf("\n\nTeste via terminal: \n\n");

    int opcao, pos, valor;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir elemento\n");
        printf("2. Retirar elemento\n");
        printf("3. Modificar elemento\n");
        printf("4. Imprimir lista\n");
        printf("5. Obter tamanho da lista\n");
        printf("6. Obter elemento\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a posição e o valor a inserir: ");
                scanf("%d %d", &pos, &valor);
                inserirElemento(&lista, pos, valor);
                break;
            case 2:
                printf("Digite a posição do elemento a retirar: ");
                scanf("%d", &pos);
                retirarElemento(&lista, pos);
                break;
            case 3:
                printf("Digite a posição e o novo valor: ");
                scanf("%d %d", &pos, &valor);
                modificarElemento(&lista, pos, valor);
                break;
            case 4:
                imprimeLista(&lista);
                break;
            case 5:
                printf("Tamanho da lista: %d\n", obterTamanho(&lista));
                break;
            case 6:
                printf("Digite a posição do elemento: ");
                scanf("%d", &pos);
                printf("Elemento na posição %d: %d\n", pos, obterElemento(&lista, pos));
                break;
            case 0:
                exit(0);
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}
