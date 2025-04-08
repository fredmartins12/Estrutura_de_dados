#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

int matriz[MAX][MAX];
bool visitado[MAX];
int adj[MAX][MAX];
int graus[MAX];
int num_vertices;

void carregar_grafo(const char *nome_arquivo) {
    FILE *fp = fopen(nome_arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    int u, v;
    fscanf(fp, "%d", &num_vertices);
    while (fscanf(fp, "%d %d", &u, &v) != EOF) {
        matriz[u][v] = 1;
        matriz[v][u] = 1;
        adj[u][graus[u]++] = v;
        adj[v][graus[v]++] = u;
    }
    fclose(fp);
}

void bfs(int s, int t) {
    int fila[MAX], pai[MAX];
    int ini = 0, fim = 0;
    bool visitado_bfs[MAX] = {false};

    fila[fim++] = s;
    visitado_bfs[s] = true;
    pai[s] = -1;

    while (ini < fim) {
        int u = fila[ini++];
        for (int i = 0; i < graus[u]; i++) {
            int v = adj[u][i];
            if (!visitado_bfs[v]) {
                visitado_bfs[v] = true;
                fila[fim++] = v;
                pai[v] = u;
            }
        }
    }

    if (!visitado_bfs[t]) {
        printf("Nao ha caminho entre %d e %d\n", s, t);
        return;
    }

    int caminho[MAX], tam = 0;
    for (int v = t; v != -1; v = pai[v])
        caminho[tam++] = v;

    printf("Caminho de %d para %d: ", s, t);
    for (int i = tam - 1; i >= 0; i--)
        printf("%d ", caminho[i]);
    printf("\n");
}

void dfs_iterativo(int inicio) {
    int pilha[MAX], topo = -1;
    for (int i = 0; i < num_vertices; i++) visitado[i] = false;

    pilha[++topo] = inicio;

    while (topo >= 0) {
        int u = pilha[topo--];
        if (!visitado[u]) {
            printf("Visitando %d\n", u);
            visitado[u] = true;
            for (int i = graus[u] - 1; i >= 0; i--) {
                int v = adj[u][i];
                if (!visitado[v])
                    pilha[++topo] = v;
            }
        }
    }
}