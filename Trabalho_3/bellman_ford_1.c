#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 1000
#define MAX_EDGES 1000

typedef struct Edge {
    int source;
    int dest;
    int weight;
} Edge;

void bellman_ford(int num_vertices, int num_edges, Edge *edges, int start_vertex) {
    int dist[MAX_VERTICES];
    
    // inicializa distâncias
    for (int i = 1; i <= num_vertices; i++) {
        dist[i] = INT_MAX;
    }
    dist[start_vertex] = 0;
    
    // relaxa todas as arestas V-1 vezes
    for (int i = 1; i <= num_vertices; i++) {
        for (int j = 1; j <= num_edges; j++) {

            int u = edges[j].source;
            int v = edges[j].dest;
            int weight = edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    
    // verifica se há ciclos de peso negativo
    for (int i = 1; i <= num_edges; i++) {

        int u = edges[i].source;
        int v = edges[i].dest;
        int weight = edges[i].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("O grafo contem um ciclo de peso negativo\n");
            return;
        }
    }
    
    // imprime as distâncias mais curtas
    printf("Distancias mais curtas do vertice %d:\n", start_vertex);
    for (int i = 1; i <= num_vertices; i++) {

        if (dist[i] > 1000){
            printf("%d %s\n", i, "INF");
        }
        else{
            printf("%d: %d\n", i, dist[i]);
        }
    }
}

int main() {

    int num_vertices = 6, num_edges = 11;
    Edge edges[MAX_EDGES];

    edges[1].source = 1, edges[1].dest = 2, edges[1].weight = 12;
    edges[2].source = 1, edges[2].dest = 3, edges[2].weight = 4;
    edges[3].source = 2, edges[3].dest = 3, edges[3].weight = 6;
    edges[4].source = 2, edges[4].dest = 4, edges[4].weight = 6;
    edges[5].source = 3, edges[5].dest = 2, edges[5].weight = 10;
    edges[6].source = 3, edges[6].dest = 4, edges[6].weight = 2;
    edges[7].source = 3, edges[7].dest = 5, edges[7].weight = 2;
    edges[8].source = 4, edges[8].dest = 3, edges[8].weight = 8;
    edges[9].source = 4, edges[9].dest = 6, edges[9].weight = 6;
    edges[10].source = 5, edges[10].dest = 2, edges[10].weight = 2;
    edges[11].source = 5, edges[11].dest = 6, edges[11].weight = 6;

    printf("\n\n1 Questao Letra B Grafo 1\n\n");

    for (int i = 1; i <= num_vertices; i++){
        bellman_ford(num_vertices, num_edges, edges, i); // executa o algoritmo de Bellman-Ford
        printf("\n\n");
    }


    num_vertices = 5, num_edges = 9;
    
    edges[1].source = 1, edges[1].dest = 2, edges[1].weight = 1;
    edges[2].source = 1, edges[2].dest = 5, edges[2].weight = 1;
    edges[3].source = 2, edges[3].dest = 3, edges[3].weight = 1;
    edges[4].source = 2, edges[4].dest = 4, edges[4].weight = 2;
    edges[5].source = 3, edges[5].dest = 4, edges[5].weight = 4;
    edges[6].source = 3, edges[6].dest = 5, edges[6].weight = 2;
    edges[7].source = 4, edges[7].dest = 1, edges[7].weight = 3;
    edges[8].source = 5, edges[8].dest = 4, edges[8].weight = 1;
    edges[9].source = 5, edges[9].dest = 1, edges[9].weight = 2;

    printf("\n\n1 Questao Letra B Grafo 2\n\n");

    for (int i = 1; i <= num_vertices; i++){
        bellman_ford(num_vertices, num_edges, edges, i); // executa o algoritmo de Bellman-Ford
        printf("\n\n");
    }

    
    return 0;
}
