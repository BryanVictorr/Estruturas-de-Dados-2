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
    int altura;

}No;

No *criarNo(int info);
No *inserir(No *raiz, int info);
No *balancear(No *raiz);
No *rotacaoEsq(No *raiz);
No *rotacaoDir(No *raiz);
No *rotacaoDirEsq(No *raiz);
No *rotacaoEsqDir(No *raiz);
int maior(int a, int b);
int alturaNo(No *no);
int fatorBalanceamento(No *no);
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
    No *raiz = NULL;

    do{
        printf("\n1-Criar Arvores\n2-Sair\n");
        scanf("%d", &op);

        switch (op){

        case 1:

            for(int j = 0; j < quant_arvores; j++){

                temp_inserir = clock();
                for(int i = 0; i < TAM; i++)
                    raiz = inserir(raiz, vetor_valores[i]);
                temp_inserir = clock() - temp_inserir;

                temp_busca = clock();
                for(int k = 1; k <= 2000; k++)
                    busca(raiz, 20 * k);
                temp_busca = clock() - temp_busca;

                prof_MAX = profundidadeMax(raiz);
                prof_MIN = profundidadeMin(raiz);

                vetor_prof[j] = prof_MAX - prof_MIN;

                printf("Dados da Arvore N: %d\n\n", j + 1);
                printf("Profundidade Maxima: %d\n", prof_MAX);
                printf("Profundidade Minima: %d\n", prof_MIN);
                printf("Distancia entre as Profundidades: %d\n", prof_MAX - prof_MIN);
                printf("Tempo para inserir: %lf milissegundos\n", ((double)temp_inserir)/((CLOCKS_PER_SEC/1000)));
                printf("Tempo para busca: %lf milissegundos\n\n", ((double)temp_busca)/((CLOCKS_PER_SEC/1000)));

                embaralhaVetor(vetor_valores);
                liberarArvore(raiz);
                raiz = NULL;
            }

            verificarRepeticao(vetor_prof);
            break;

        case 2:

            printf("encerrando...");
            liberarArvore(raiz);
            free(vetor_valores);
            free(vetor_prof);
            break;
            break;
        }
    }while(op != 2);
}

No* criarNo(int info){

    No *novo = (No*) malloc(sizeof(No));
    novo->info = info;
    novo->direita = NULL;
    novo->esquerda = NULL;
    novo->altura = 0;

    return novo;
}

No* inserir(No *raiz, int info){

    if(raiz == NULL)
        return criarNo(info);
    else{
        if(info < raiz->info)
            raiz->esquerda = inserir(raiz->esquerda, info);
        else if(info > raiz->info)
            raiz->direita = inserir(raiz->direita, info);
    }

    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    raiz = balancear(raiz);

    return raiz;
}

No* balancear(No *raiz){

    int fb = fatorBalanceamento(raiz);

    if(fb < -1 && fatorBalanceamento(raiz->direita) <= 0)
        raiz = rotacaoEsq(raiz);

    else if(fb > 1 && fatorBalanceamento(raiz->esquerda) >= 0)
        raiz = rotacaoDir(raiz);

    else if(fb > 1 && fatorBalanceamento(raiz->esquerda) < 0)
        raiz = rotacaoEsqDir(raiz);

    else if(fb < -1 && fatorBalanceamento(raiz->direita) > 0)
        raiz = rotacaoDirEsq(raiz);

    return raiz;
}

No* rotacaoEsq(No *raiz){

    No *novo, *aux;

    novo = raiz->direita;
    aux = novo->esquerda;

    novo->esquerda = raiz;
    raiz->direita = aux;

    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    novo->altura = maior(alturaNo(novo->esquerda), alturaNo(novo->direita)) + 1;

    return novo;
}

No* rotacaoDir(No *raiz){

    No *novo, *aux;

    novo = raiz->esquerda;
    aux = novo->direita;

    novo->direita = raiz;
    raiz->esquerda = aux;

    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    novo->altura = maior(alturaNo(novo->esquerda), alturaNo(novo->direita)) + 1;

    return novo;
}

No* rotacaoDirEsq(No *raiz){

    raiz->direita = rotacaoDir(raiz->direita);
    return rotacaoEsq(raiz);
}

No* rotacaoEsqDir(No *raiz){

    raiz->esquerda = rotacaoEsq(raiz->esquerda);
    return rotacaoDir(raiz);
}

int maior(int a, int b){
    return (a > b) ? a : b;
}

int alturaNo(No *no){

    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento(No *no){

    if(no != NULL)
        return (alturaNo(no->esquerda) - alturaNo(no->direita));
    else
        return 0;
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

// void imprimir(No *raiz, int nivel){

//     int i;

//     if(raiz){
//         imprimir(raiz->direita, nivel + 1);
//         printf("\n\n");
    

//         for(i = 0; i < nivel; i++){
//             printf("\t"); 
//         }
//         printf("%d", raiz->info);
//         imprimir(raiz->esquerda, nivel + 1);
//     }
// }

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
