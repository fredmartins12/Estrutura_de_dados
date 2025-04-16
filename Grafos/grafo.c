#include <stdio.h>        // Biblioteca padrão para entrada e saída
#include <stdlib.h>       // Biblioteca para funções como malloc, exit, etc.
#include <stdbool.h>      // Biblioteca para usar o tipo bool (true/false)

#define MAX 100           // Define o número máximo de vértices como 100

// Matrizes e vetores globais
int matriz[MAX][MAX];     // Matriz de adjacência do grafo
bool visitado[MAX];       // Vetor de controle de vértices visitados para DFS
int adj[MAX][MAX];        // Lista de adjacência
int graus[MAX];           // Armazena o grau de cada vértice
int num_vertices;         // Número total de vértices no grafo

// Função para carregar o grafo a partir de um arquivo
void carregar_grafo(const char *nome_arquivo) {
    FILE *fp = fopen(nome_arquivo, "r"); // Abre o arquivo em modo leitura
    if (!fp) {                           // Verifica se houve erro ao abrir
        perror("Erro ao abrir arquivo"); // Exibe erro
        exit(1);                         // Encerra o programa
    }

    int u, v;
    fscanf(fp, "%d", &num_vertices);     // Lê o número de vértices do grafo
    while (fscanf(fp, "%d %d", &u, &v) != EOF) { // Lê arestas até o fim do arquivo
        matriz[u][v] = 1;                // Marca conexão na matriz de adjacência
        matriz[v][u] = 1;                // Como é não direcionado, marca inverso também
        adj[u][graus[u]++] = v;          // Adiciona v na lista de adjacência de u
        adj[v][graus[v]++] = u;          // Adiciona u na lista de adjacência de v
    }
    fclose(fp);                          // Fecha o arquivo
}

// Busca em largura entre dois vértices s (origem) e t (destino)
void bfs(int s, int t) {
    int fila[MAX], pai[MAX];             // Fila da BFS e vetor de pais
    int ini = 0, fim = 0;                // Ponteiros da fila
    bool visitado_bfs[MAX] = {false};    // Vetor de visitados para BFS, inicializado como falso

    fila[fim++] = s;                     // Insere o vértice inicial na fila
    visitado_bfs[s] = true;              // Marca como visitado
    pai[s] = -1;                         // S não tem pai (é o início)

    while (ini < fim) {                  // Enquanto houver elementos na fila
        int u = fila[ini++];             // Remove o primeiro da fila
        for (int i = 0; i < graus[u]; i++) { // Percorre todos os vizinhos de u
            int v = adj[u][i];           // Vizinho atual
            if (!visitado_bfs[v]) {      // Se ainda não foi visitado
                visitado_bfs[v] = true;  // Marca como visitado
                fila[fim++] = v;         // Adiciona à fila
                pai[v] = u;              // Registra o pai de v
            }
        }
    }

    if (!visitado_bfs[t]) {              // Se t não foi visitado, não há caminho
        printf("Nao ha caminho entre %d e %d\n", s, t);
        return;
    }

    int caminho[MAX], tam = 0;           // Vetor para armazenar o caminho e seu tamanho
    for (int v = t; v != -1; v = pai[v]) // Reconstrói o caminho de t até s
        caminho[tam++] = v;

    printf("Caminho de %d para %d: ", s, t);
    for (int i = tam - 1; i >= 0; i--)   // Imprime o caminho do início ao fim
        printf("%d ", caminho[i]);
    printf("\n");
}

// Busca em profundidade iterativa a partir do vértice 'inicio'
void dfs_iterativo(int inicio) {
    int pilha[MAX], topo = -1;          // Pilha e topo da pilha
    for (int i = 0; i < num_vertices; i++) 
        visitado[i] = false;            // Inicializa todos como não visitados

    pilha[++topo] = inicio;             // Empilha o vértice inicial

    while (topo >= 0) {                 // Enquanto a pilha não estiver vazia
        int u = pilha[topo--];          // Desempilha o topo
        if (!visitado[u]) {             // Se ainda não foi visitado
            printf("Visitando %d\n", u); // Marca a visita
            visitado[u] = true;
            for (int i = graus[u] - 1; i >= 0; i--) { // Percorre os vizinhos de u
                int v = adj[u][i];      // Vizinho atual
                if (!visitado[v])       // Se ainda não visitado
                    pilha[++topo] = v;  // Empilha o vizinho
            }
        }
    }
}
