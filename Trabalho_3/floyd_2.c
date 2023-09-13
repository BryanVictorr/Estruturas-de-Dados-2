#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX
#define V 4

void floyd(int grafo[][V]);
void imprime_matriz(int matriz[][V], int m_matriz);
void distancia_dos_pontos(int matriz[][V]);

int main(){

    //Grafo da 2
    int grafo[V][V] = {
        {0, 3, INF, 7},
        {8, 0, 2, INF},
        {5, INF, 0, 1},
        {2, INF, INF, 0},
    };

    floyd(grafo);
    return 0;
}


void floyd(int grafo[][V]){

    int i, j, k;
    int matriz[V][V];

    // Faz uma copia do Grafo original para uma Matriz
    for (i = 0; i < V; i++){
        for (j = 0; j < V; j++){
            matriz[i][j] = grafo[i][j];
        }
    }

    // Aplica o Algoritmo de Floyd-Warshall
    for (k = 0; k < V; k++){
        for (i = 0; i < V; i++){
            for (j = 0; j < V; j++){

                if (matriz[i][k] != INF && matriz[k][j] != INF && matriz[i][j] > matriz[i][k] + matriz[k][j]) {
                    matriz[i][j] = matriz[i][k] + matriz[k][j];
                }
            }
        }
        imprime_matriz(matriz,k); // Imprime a Matriz uma por vez
    }
}

// Função para imprimir a matiz alinhada
void imprime_matriz(int matriz[][V], int m_matriz){

    if (m_matriz < V - 1){
        printf("\n\nMatriz M%d\n\n",m_matriz);
    }
    else{
        printf("\n\nMatriz Final\n\n");
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {

            if (matriz[i][j] == INF){
                printf("%7s", "INF"); // "%7s" informa para imprimir a string e completar os espaço em branco até fechar 7 caracter
            }
            else{
                printf("%7d", matriz[i][j]); // "%7s" informa para imprimir a string e completar os espaço em branco até fechar 7 caracter
            }
        }
        printf("\n");
    }

    if (m_matriz == V - 1){
        printf("\n\n2 Questao\n");
        distancia_dos_pontos(matriz);
    }
}

//Função vai imprimir a disntacia de todos os pontos da Matriz
void distancia_dos_pontos(int matriz[][V]){

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("Distancia de %c -> %c = %d\n", 65 + i, 65 + j, matriz[i][j]);
        }
        printf("\n");
    }
}