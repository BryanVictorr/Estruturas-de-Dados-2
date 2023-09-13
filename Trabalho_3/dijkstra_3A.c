#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define MAX_EDGES 100

typedef struct Edge {
    int start;
    int dest;
    int weight;
} Edge;

void dijkstra(int num_vertices, int num_edges, Edge *edges, int start_vertex) {

    int visited[MAX_VERTICES] = { 0 };
    int dist[MAX_VERTICES];
    int prev[MAX_VERTICES];
    
    // inicializa distâncias
    for (int i = 1; i <= num_vertices; i++) {
        dist[i] = INT_MAX;
    }
    dist[start_vertex] = 0;
    
    // encontra a menor distância para cada vértice
    for (int i = 1; i <= num_vertices - 1; i++) {
        int min_dist = INT_MAX, current_vertex;
        
        // encontra o vértice não visitado com a menor distância
        for (int j = 1; j <= num_vertices; j++) {
            if (!visited[j] && dist[j] <= min_dist) {
                min_dist = dist[j];
                current_vertex = j;
            }
        }
        
        // marca o vértice como visitado
        visited[current_vertex] = 1;
        
        // relaxa todas as arestas do vértice atual
        for (int j = 1; j <= num_edges; j++) {
            int start = edges[j].start;
            int dest = edges[j].dest;
            int weight = edges[j].weight;
            if (current_vertex == start && dist[current_vertex] != INT_MAX && dist[current_vertex] + weight < dist[dest]) {
                dist[dest] = dist[current_vertex] + weight;
                prev[dest] = current_vertex;
            }
        }
    }

    printf("Caminho mais curto do vertice %c a todos os outros:\n\n", 64+start_vertex);
    for (int i = 1; i <= num_vertices; i++) {

        printf("%c: ", 64+i);

        if (dist[i] == INT_MAX) {
            printf("inacessivel\n\n");
        }
        else{

            printf("%c", 64+i);
            int current_vertex = i;

            while (current_vertex != start_vertex) {

                current_vertex = prev[current_vertex];
                printf(" <- %c", 64+current_vertex);
            }
            printf("\nDistancia: %d\n\n", dist[i]);
        }
    }
}


int main() {
    
    int num_vertices = 10, num_edges = 18;
    Edge edges[MAX_EDGES];
    
    edges[1].start = 1, edges[1].dest = 2, edges[1].weight = 4;
    edges[2].start = 1, edges[2].dest = 3, edges[2].weight = 1;
    edges[3].start = 1, edges[3].dest = 4, edges[3].weight = 3;
    edges[4].start = 2, edges[4].dest = 5, edges[4].weight = 3;
    edges[5].start = 2, edges[5].dest = 3, edges[5].weight = 1;
    edges[6].start = 3, edges[6].dest = 4, edges[6].weight = 1;
    edges[7].start = 3, edges[7].dest = 5, edges[7].weight = 7;
    edges[8].start = 3, edges[8].dest = 6, edges[8].weight = 6;
    edges[9].start = 4, edges[9].dest = 6, edges[9].weight = 2;
    edges[10].start = 4, edges[10].dest = 7, edges[10].weight = 3;
    edges[11].start = 4, edges[11].dest = 8, edges[11].weight = 2;
    edges[12].start = 5, edges[12].dest = 6, edges[12].weight = 1;
    edges[13].start = 5, edges[13].dest = 9, edges[13].weight = 2;
    edges[14].start = 6, edges[14].dest = 9, edges[14].weight = 4;
    edges[15].start = 7, edges[15].dest = 8, edges[15].weight = 5;
    edges[16].start = 7, edges[16].dest = 9, edges[16].weight = 4;
    edges[17].start = 8, edges[17].dest = 10, edges[17].weight = 2;
    edges[18].start = 9, edges[18].dest = 10, edges[18].weight = 1;

    // executa o algoritmo de Dijkstra

    printf("\n\n3 Questao Letra A\n\n");

    dijkstra(num_vertices, num_edges, edges, 1);

    return 0;
}