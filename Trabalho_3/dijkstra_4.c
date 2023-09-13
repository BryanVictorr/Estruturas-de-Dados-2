#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 200
#define MAX_EDGES 200

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

    int num_vertices = 10, num_edges = 54;
    Edge edges[MAX_EDGES];


    edges[1].start = 1, edges[1].dest = 2, edges[1].weight = 6;
    edges[2].start = 1, edges[2].dest = 3, edges[2].weight = 8;
    edges[3].start = 1, edges[3].dest = 4, edges[3].weight = 10;
    edges[4].start = 2, edges[4].dest = 1, edges[4].weight = 6;
    edges[5].start = 2, edges[5].dest = 3, edges[5].weight = 12;
    edges[6].start = 2, edges[6].dest = 4, edges[6].weight = 14;
    edges[7].start = 2, edges[7].dest = 5, edges[7].weight = 18;
    edges[8].start = 3, edges[8].dest = 1, edges[8].weight = 8;
    edges[9].start = 3, edges[9].dest = 2, edges[9].weight = 12;
    edges[10].start = 3, edges[10].dest = 4, edges[10].weight = 22;
    edges[11].start = 3, edges[11].dest = 5, edges[11].weight = 24;
    edges[12].start = 3, edges[12].dest = 6, edges[12].weight = 28;
    edges[13].start = 3, edges[13].dest = 7, edges[13].weight = 30;
    edges[14].start = 4, edges[14].dest = 1, edges[14].weight = 10;
    edges[15].start = 4, edges[15].dest = 2, edges[15].weight = 14;
    edges[16].start = 4, edges[16].dest = 3, edges[16].weight = 22;
    edges[17].start = 4, edges[17].dest = 5, edges[17].weight = 18;
    edges[18].start = 4, edges[18].dest = 6, edges[18].weight = 16;
    edges[19].start = 4, edges[19].dest = 7, edges[19].weight = 14;
    edges[20].start = 5, edges[20].dest = 2, edges[20].weight = 18;
    edges[21].start = 5, edges[21].dest = 3, edges[21].weight = 24;
    edges[22].start = 5, edges[22].dest = 4, edges[22].weight = 18;
    edges[23].start = 5, edges[23].dest = 6, edges[23].weight = 38;
    edges[24].start = 5, edges[24].dest = 7, edges[24].weight = 40;
    edges[25].start = 5, edges[25].dest = 8, edges[25].weight = 46;
    edges[26].start = 5, edges[26].dest = 9, edges[26].weight = 52;
    edges[27].start = 6, edges[27].dest = 3, edges[27].weight = 28;
    edges[28].start = 6, edges[28].dest = 4, edges[28].weight = 16;
    edges[29].start = 6, edges[29].dest = 5, edges[29].weight = 38;
    edges[30].start = 6, edges[30].dest = 7, edges[30].weight = 54;
    edges[31].start = 6, edges[31].dest = 8, edges[31].weight = 58;
    edges[32].start = 6, edges[32].dest = 9, edges[32].weight = 60;
    edges[33].start = 6, edges[33].dest = 10, edges[33].weight = 62;
    edges[34].start = 7, edges[34].dest = 3, edges[34].weight = 30;
    edges[35].start = 7, edges[35].dest = 4, edges[35].weight = 24;
    edges[36].start = 7, edges[36].dest = 5, edges[36].weight = 40;
    edges[37].start = 7, edges[37].dest = 6, edges[37].weight = 54;
    edges[38].start = 7, edges[38].dest = 8, edges[38].weight = 80;
    edges[39].start = 7, edges[39].dest = 9, edges[39].weight = 82;
    edges[40].start = 7, edges[40].dest = 10, edges[40].weight = 84;
    edges[41].start = 8, edges[41].dest = 5, edges[41].weight = 46;
    edges[42].start = 8, edges[42].dest = 6, edges[42].weight = 58;
    edges[43].start = 8, edges[43].dest = 7, edges[43].weight = 80;
    edges[44].start = 8, edges[44].dest = 9, edges[44].weight = 100;
    edges[45].start = 8, edges[45].dest = 10, edges[45].weight = 110;
    edges[46].start = 9, edges[46].dest = 5, edges[46].weight = 52;
    edges[47].start = 9, edges[47].dest = 6, edges[47].weight = 60;
    edges[48].start = 9, edges[48].dest = 7, edges[48].weight = 82;
    edges[49].start = 9, edges[49].dest = 8, edges[49].weight = 100;
    edges[50].start = 9, edges[50].dest = 10, edges[50].weight = 120;
    edges[51].start = 10, edges[51].dest = 6, edges[51].weight = 62;
    edges[52].start = 10, edges[52].dest = 7, edges[52].weight = 84;
    edges[53].start = 10, edges[53].dest = 8, edges[53].weight = 110;
    edges[54].start = 10, edges[54].dest = 9, edges[54].weight = 120;
    
    // executa o algoritmo de Dijkstra

    printf("\n\n4 Questao Letra A\n\n");
    dijkstra(num_vertices, num_edges, edges, 1);

    printf("\n\n");

    printf("\n\n4 Questao Letra B\n\n");
    dijkstra(num_vertices, num_edges, edges, 10);

    return 0;
}