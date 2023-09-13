#include <stdio.h>
#include <stdlib.h>
#include <time.h> //clock(), CLOCKS_PER_SEC e clock_t

#define TAM 20000 // Quantidade de Elementos que a Arvore vai possuir
#define intervalo TAM*2 // Intervalo entra os valores que a arvore vai amazenar
#define quant_arvores 30 //Quantidade de Arvores criadas

typedef struct no{

    int info;
    struct no *esquerda;
    struct no *direita;

}No;

typedef struct{

    No *raiz;

}ArvoreBin;

void inicializar(ArvoreBin *arv);
void inserir(ArvoreBin *arv, int info);
void inserirEsquerda(No *no, int info);
void inserirDireita(No *no, int info);
int busca(No *raiz, int info);
void gerarNumeros(int *vetor);
void embaralhaVetor(int *vetor);
int profundidadeMax(No *raiz);
int profundidadeMin(No *raiz);
void verificarRepeticao(int *vetor);
void liberarArvore(No *raiz);

void main(){

    srand(time(NULL));

    clock_t temp_inserir, temp_busca;
    int op, prof_MAX, prof_MIN;
    int *vetor_valores = (int*) malloc(TAM * sizeof(int));
    int *vetor_prof = (int*) malloc(quant_arvores * sizeof(int));
    
    gerarNumeros(vetor_valores);

    ArvoreBin arv;
    inicializar(&arv);

    do{
        printf("\n1 - Criar Arvores\n2 - Encerrar\n");
        scanf("%d", &op);

        switch (op){

        case 1:

            for(int j = 0; j < quant_arvores; j++){

                temp_inserir = clock();
                
                for(int i = 0; i < TAM; i++)
                    inserir(&arv, vetor_valores[i]);

                temp_inserir = clock() - temp_inserir;

                temp_busca = clock();

                for(int i = 1; i <= 2000; i++)
                    busca(arv.raiz, 20 * i);

                temp_busca = clock() - temp_busca;

                prof_MAX = profundidadeMax(arv.raiz);
                prof_MIN = profundidadeMin(arv.raiz);

                vetor_prof[j] = prof_MAX - prof_MIN;

                printf("Dados da Arvore N: %d\n\n", j + 1);
                printf("Profundidade Maxima: %d\n", prof_MAX);
                printf("Profundidade Minima: %d\n", prof_MIN);
                printf("Distancia entre as Profundidades: %d\n", prof_MAX - prof_MIN);
                printf("Tempo para inserir: %lf milissegundos\n", ((double)temp_inserir)/((CLOCKS_PER_SEC/1000)));
                printf("Tempo para busca: %lf milissegundos\n\n", ((double)temp_busca)/((CLOCKS_PER_SEC/1000)));

                embaralhaVetor(vetor_valores);
                liberarArvore(arv.raiz);
                arv.raiz = NULL;
            }

            verificarRepeticao(vetor_prof);
            break;

        case 2:

            printf("Encerrando...\n");
            liberarArvore(arv.raiz);
            free(vetor_valores);
            free(vetor_prof);
            break;
        
        default:

            printf("\nOpcao invalida...");
            break;
        }

    }while(op != 2);
}

void inicializar(ArvoreBin *arv){
    arv->raiz = NULL;
}

void inserir(ArvoreBin *arv, int info){

    if(arv->raiz == NULL){

        No *novo = (No*)malloc(sizeof(No));
        novo->info = info;
        novo->direita = NULL;
        novo->esquerda = NULL;
        arv->raiz = novo;
    }
    else{

        if(info < arv->raiz->info)
            inserirEsquerda(arv->raiz, info);
        if(info > arv->raiz->info)
            inserirDireita(arv->raiz, info);
    }
}

void inserirEsquerda(No *no, int info){

    if(no->esquerda == NULL){

        No *novo = (No*)malloc(sizeof(No));
        novo->info = info;
        novo->direita = NULL;
        novo->esquerda = NULL;
        no->esquerda = novo;
    }
    else{

        if(info < no->esquerda->info)
            inserirEsquerda(no->esquerda, info);
        if(info > no->esquerda->info)
            inserirDireita(no->esquerda, info);
    }
}

void inserirDireita(No *no, int info){

    if(no->direita == NULL){

        No *novo = (No*)malloc(sizeof(No));
        novo->info = info;
        novo->direita = NULL;
        novo->esquerda = NULL;
        no->direita = novo;
    }
    else{

        if(info > no->direita->info)
            inserirDireita(no->direita, info);
        if(info < no->direita->info)
            inserirEsquerda(no->direita, info);
    }    
}

int busca(No *raiz, int info){

    if(raiz == NULL)
        return 0;

    else{

        if(raiz->info == info)
            return 1;

        else{

            if(info < raiz->info)
                return busca(raiz->esquerda, info);
            else
                return busca(raiz->direita, info);
        }
    }
}

void gerarNumeros(int *vetor){

    srand(time(NULL));

    int i = 0, aux = 0;

    while (i < TAM){

        *(vetor + i) = 1 + rand() % intervalo;
        aux = 0;

        for(int x = 0; x < i; x++){

            if(*(vetor + i) == *(vetor + x))
                aux = 1;
        }
        if(aux == 0)
            i++;
    }
}

void embaralhaVetor(int *vetor){

	for (int i = 0; i < TAM; i++){

		int r = rand() % TAM;
		int temp = vetor[i];
		vetor[i] = vetor[r];
		vetor[r] = temp;
	}
}

int profundidadeMax(No *raiz){

    int aux, esq = 0, dir = 0;

    if(raiz == NULL){
        aux = -1;
    }
    else{

        if(raiz->esquerda == NULL && raiz->direita == NULL){
            aux = 0;
        }
        else{

            esq = profundidadeMax(raiz->esquerda);
            dir = profundidadeMax(raiz->direita);

            

            if(esq != -1 && dir != 1){

                if(esq > dir){
                    esq++;
                    aux = esq;
                }
                else{
                    dir++;
                    aux = dir;
                }
            }
            else{

                if(esq != -1){
                    esq++;
                    aux = esq;
                }
                else{
                    dir++;
                    aux = dir;
                }
            }
        }
    }
    return aux;
}

int profundidadeMin(No *raiz){
    
    int aux, esq = 0, dir = 0;

    if(raiz == NULL){
        aux = -1;
    }
    else{

        if(raiz->esquerda == NULL && raiz->direita == NULL){
            aux = 0;
        }
        else{

            esq = profundidadeMin(raiz->esquerda);
            dir = profundidadeMin(raiz->direita);

            if(esq != -1 && dir != 1){

                if(esq < dir){
                    esq++;
                    aux = esq;
                }
                else{
                    dir++;
                    aux = dir;
                }
            }
            else{

                if(esq != -1){
                    esq++;
                    aux = esq;
                }
                else{
                    dir++;
                    aux = dir;
                }
            }
        }
    }
    return aux;
}

void verificarRepeticao(int *vetor){

    int verificar = 0, aux = 0, cont = 0;
    int *vetor_repet = (int*) malloc(quant_arvores * sizeof(int));

    for(int i = 0; i < quant_arvores; i++){
        vetor_repet[i] = -1;
    }

    for(int i = 0; i < quant_arvores; i++){
        for(int j = 0; j < quant_arvores; j++){

            if(vetor[i] == vetor[j])
                cont++;

        }
        for(int k = 0; k < quant_arvores; k++){

            if(vetor[i] == vetor_repet[k])
                verificar = 1;
        }
        if(verificar == 0){
            
            vetor_repet[aux] = vetor[i];
            printf("Distancia entre Profundidades %d repetiu %d vezes\n", vetor_repet[aux], cont);
            aux++;
        }
        verificar = 0;
        cont = 0;
    }
    free(vetor_repet);
}

void liberarArvore(No *raiz){

    if(raiz != NULL){

        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}