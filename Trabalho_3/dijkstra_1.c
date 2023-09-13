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

void imprime_grafo_alfa(int num_vertices, int start_vertex,int dist[],int prev[]);
void imprime_grafo_num(int num_vertices, int start_vertex, int dist[], int prev[]);

void dijkstra(int num_vertices, int num_edges, Edge *edges, int start_vertex, int tipo) {

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
    if (tipo == 0){
        imprime_grafo_alfa(num_vertices, start_vertex, dist, prev);
    }
    else{
        imprime_grafo_num(num_vertices, start_vertex, dist, prev);
    }
    
}

void imprime_grafo_alfa(int num_vertices, int start_vertex, int dist[], int prev[]){

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

void imprime_grafo_num(int num_vertices, int start_vertex, int dist[], int prev[]){

    printf("Caminho mais curto do vertice %d a todos os outros:\n\n", start_vertex);
    for (int i = 1; i <= num_vertices; i++) {

        printf("%d: ",i);

        if (dist[i] == INT_MAX) {
            printf("inacessivel\n\n");
        }
        else{

            printf("%d", i);
            int current_vertex = i;

            while (current_vertex != start_vertex) {

                current_vertex = prev[current_vertex];
                printf(" <- %d", current_vertex);
            }
            printf("\nDistancia: %d\n\n", dist[i]);
        }
    }
}

int main() {

    int num_vertices = 6, num_edges = 11;
    Edge edges[MAX_EDGES];
    
    edges[1].start = 1, edges[1].dest = 2, edges[1].weight = 12;
    edges[2].start = 1, edges[2].dest = 3, edges[2].weight = 4;
    edges[3].start = 2, edges[3].dest = 3, edges[3].weight = 6;
    edges[4].start = 2, edges[4].dest = 4, edges[4].weight = 6;
    edges[5].start = 3, edges[5].dest = 2, edges[5].weight = 10;
    edges[6].start = 3, edges[6].dest = 4, edges[6].weight = 2;
    edges[7].start = 3, edges[7].dest = 5, edges[7].weight = 2;
    edges[8].start = 4, edges[8].dest = 3, edges[8].weight = 8;
    edges[9].start = 4, edges[9].dest = 6, edges[9].weight = 6;
    edges[10].start = 5, edges[10].dest = 2, edges[10].weight = 2;
    edges[11].start = 5, edges[11].dest = 6, edges[11].weight = 6;
    
    
    // executa o algoritmo de Dijkstra

    printf("\n\n1 Questao Grafo 1\n\n");

    for(int i = 1; i <= 6; i++){
        dijkstra(num_vertices, num_edges, edges, i, 0);
        printf("\n");
    }

    num_vertices = 5, num_edges = 9;

    edges[1].start = 1, edges[1].dest = 2, edges[1].weight = 1;
    edges[2].start = 1, edges[2].dest = 5, edges[2].weight = 1;
    edges[3].start = 2, edges[3].dest = 3, edges[3].weight = 1;
    edges[4].start = 2, edges[4].dest = 4, edges[4].weight = 2;
    edges[5].start = 3, edges[5].dest = 4, edges[5].weight = 4;
    edges[6].start = 3, edges[6].dest = 5, edges[6].weight = 2;
    edges[7].start = 4, edges[7].dest = 1, edges[7].weight = 3;
    edges[8].start = 5, edges[8].dest = 4, edges[8].weight = 1;
    edges[9].start = 5, edges[9].dest = 1, edges[9].weight = 2;

    printf("\n\n1 Questao Grafo 2\n\n");

    for(int i = 1; i <= 5; i++){
        dijkstra(num_vertices, num_edges, edges, i, 1);
        printf("\n");
    }
    
    return 0;
}
