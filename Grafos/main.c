#include <stdio.h>

void carregar_grafo(const char *nome_arquivo);
void bfs(int s, int t);
void dfs_iterativo(int inicio);

int main() {
    carregar_grafo("grafo1.txt");

    printf("BFS entre 0 e 4:\n");
    bfs(0, 4);

    printf("\nDFS a partir do vertice 0:\n");
    dfs_iterativo(0);

    return 0;
}