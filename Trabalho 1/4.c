#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#define TAM 6  //quantidade de unidades que serao lidas

//calcula o tempo de execucao
double calcula_tempo(clock_t tempo[2]){  

    double Tempo_ex;
	Tempo_ex = (tempo[1] - 	tempo[0]) * 1000.0 / CLOCKS_PER_SEC;

    return Tempo_ex;
}

typedef struct{
	
	char palavra[50];

}palavras;

typedef struct{

	char ingles[50];
	palavras portugues[10];
	int quant;
	
}vocabulario;

//carrega a lista de palavras do arquivo
void open_file(FILE **file,char arquivo[50]){

	*file = fopen(arquivo,"r");

	if (*file == NULL){
	 	printf("\nERRO: nao foi possivel abrir arquivo!!\n");
    }
}

//recebe uma lista do arquivo depois armazena no vocabulario removendos os caracter especiais
void trata_string(vocabulario *v, char frase[200]){

    int i=0, tam;
    char *t,*aux;
    char texto1[200];

    tam = strlen(frase)-1;  

    strncpy(texto1, frase, strlen(frase)-1);  // elimina quebra de linha da string

    texto1[tam] = '\0';
      
    t = strtok(texto1,":");
      
    while(t != NULL){
        
        if (i == 0){

            strcpy(v->ingles,t);
        
        }else{

            aux = strtok(t,",");
            v->quant = 0;

            while(aux != NULL){
 
                strcpy(v->portugues[v->quant].palavra,aux);
                v->quant++;
                aux = strtok(NULL,",");
            }
        }
        
        t = strtok(NULL,":");
        i++;
      
    }
}

typedef struct l{  //lista palavras ingles
	
	char ingles[50];
	struct l *prox;
	
}lista;

//aloca memoria para armazenar a lista de palavras
void aloca_lista_ingles(lista **No, char plv[50]){

	lista *novo;

	novo = (lista*)malloc(sizeof(lista));
	strcpy(novo->ingles, plv);
	novo->prox = NULL;
	*No = novo;
}

//imprime palavras em ingles da unidade escolhida
void imprimir_lista_ingles(lista *t){

	printf("|| ingles: ");

	while(t != NULL){

		printf("%s ,",t->ingles); 
		t = t->prox;
	}

	printf("\n");

}

//recebe um nó e insere no fim da lista
void insere_lista(lista **inicio, lista *No){ // recebe um no e insere no fim da lista
	
	lista *aux;
	
	if (*inicio == NULL){
		*inicio = No;
	}else{

		aux = *inicio; 
		
		while(aux->prox != NULL){
			aux= aux->prox;
		}  
		
		aux->prox = No;
	}
}

//recebe a palavra em ingles e adiciona na lista
void insere_plv_ingles(lista **inicio, char plv[50]){
	
	lista *No;

	aloca_lista_ingles(&No,plv);
	insere_lista(inicio,No);
}

//arvore de lista com palavaras em ingles
typedef struct b{
	
	char palavra[50];
	lista *l_ingles;
	int altura;
	struct b *esq,*dir;

}arvorebin;

//armazena arvores de palavras
typedef struct{
	
	char nome[30];
	arvorebin *arvore;

}unidades;

//cria arvore para armazenar as palavras
void aloca_arvore(arvorebin **No , char plv[50] ){
	
	arvorebin *novo;
	novo = (arvorebin *)malloc(sizeof(arvorebin));

	strcpy(novo->palavra, plv);
	
	novo->dir = novo->esq = NULL;
	novo->l_ingles = NULL;

	*No = novo;
}

int altura_no(arvorebin *Raiz){
	int h1,h2,altura;

	if (Raiz == NULL){  //se a raiz é nula sua altura é -1
		altura = -1;
	
	}else{
		
		h1 = altura_no(Raiz->esq);  //h1 recebe a altura da raiz da esquerda
		h2 = altura_no(Raiz->dir);  //h2 recebe a altura da raiz da direita


		if (h1 > h2)           // verifica qual a maior altura
							  //se h1 for maior que h2
			altura = h1+1;   // a altura sera a altura da esquerda + 1
		else
			altura = h2+1; //se nao a altura sera a altura da direita + 1

	}

	return altura; //retorna a maior altura
}

int fator_balanceamento(arvorebin *Raiz){
	return  altura_no(Raiz->esq) -  altura_no(Raiz->dir);
}

//Recebe o No desbalanceado e balanceia No onde o desbalanceamento esta para esqueda
void balanceia_esquerda(arvorebin **Raiz){

	arvorebin *No_aux;

	No_aux = (*Raiz)->esq;
	(*Raiz)->esq = No_aux->dir;

	No_aux->dir = *Raiz;
	*Raiz = No_aux;
}

// Recebe o No desbalanceado e balanceia No onde o desbalanceamento esta para direita
void balanceia_direita(arvorebin **Raiz){

	arvorebin *No_aux;

	No_aux = (*Raiz)->dir;
	(*Raiz)->dir = No_aux->esq;

	No_aux->esq = *Raiz;
	*Raiz = No_aux;
}

void verifica_balanceamento(arvorebin **Raiz){
	int fb;

	fb = fator_balanceamento(*Raiz);

	if (fb == 2){ 									//arvore esta desbalanceada para esquerda

		if (fb > 0 && fator_balanceamento((*Raiz)->esq) < 0){ //caso em que o galho maior for interno
			balanceia_direita(&(*Raiz)->esq);
		}
		
		balanceia_esquerda(Raiz);
	
	}else if (fb == -2){  						//arvore esta desbalanceada para direita


		if (fb < 0 && fator_balanceamento((*Raiz)->dir) > 0){ //caso em que o galho maior for interno
			balanceia_esquerda(&(*Raiz)->dir);
		}
		balanceia_direita(Raiz);
	}
}

//insere palavras na arvore
void insere_arvore(arvorebin **Raiz ,arvorebin *No, char plv_ingles[50]){

	if (*Raiz == NULL){  				 			 	 
		*Raiz = No;

		insere_plv_ingles(&((*Raiz)->l_ingles), plv_ingles);
	
	}else if ( strcmp(No->palavra,(*Raiz)->palavra) < 0){

		insere_arvore(&(*Raiz)->esq,No,plv_ingles);   		
			
	}else if ( strcmp(No->palavra,(*Raiz)->palavra) > 0 ){ 
		
		insere_arvore(&(*Raiz)->dir,No,plv_ingles);       	
	
//caso em que a palavra portugues ja foi inserida entao apenas insere a palavra em ingles na lista do No
	}else if( strcmp(No->palavra,(*Raiz)->palavra) == 0){
		
		insere_plv_ingles(&((*Raiz)->l_ingles), plv_ingles);
	
	}

	(*Raiz)->altura = altura_no(*Raiz);
	verifica_balanceamento(Raiz);
}

//imprime palavras da arvore
void imprimir_dicionario(arvorebin *Raiz){

	if (Raiz != NULL){
		
		imprimir_dicionario(Raiz->esq);
		printf("portugues: %s ",Raiz->palavra);
		imprimir_lista_ingles(Raiz->l_ingles);
		printf("\n");

		imprimir_dicionario(Raiz->dir);
	}
}
void insere_plv_portugues(arvorebin **Raiz , vocabulario v){

	int i;
	arvorebin *No;

	for (i = 0; i < v.quant; ++i){

		aloca_arvore(&No,v.portugues[i].palavra);
		insere_arvore(Raiz,No,v.ingles);
	}
}

//ler os dados dos arquivos e a cada unidade encontrada insere as palavras da unidade em uma arvore
void carrega_dados(FILE *file, unidades uni[TAM]){

	char frase[200],unidade[30];

	vocabulario v;

	int i,quant_unidades = -1;

    clock_t Ticks[2];

    Ticks[0] = clock();

	while(fgets(frase,200, file)){

		v.quant = 0;

		if (frase[0] == '%'){

			quant_unidades++;

			uni[quant_unidades].arvore = NULL;

			strcpy(uni[quant_unidades].nome,frase);

		}else{

			trata_string(&v,frase);
			insere_plv_portugues(&(uni[quant_unidades].arvore),v);
		}
	}

	Ticks[1] = clock();

	printf("\nTempo gasto para insercao: %g ms.", calcula_tempo(Ticks));

}

//receve vetor de arvores e o nome de uma unidade, busca e imprime a arvore de palavras da unidade
int imprimir_unidade(unidades uni[TAM],char unidade[30]){
	int i,flag=0;        
	char aux[30]="%";

	strcat(aux, unidade);

	for (i = 0; i < TAM; ++i){

		if (strncmp(uni[i].nome,aux,strlen(uni[i].nome)-1) == 0){

			printf("\n%s\n\n",unidade);
			imprimir_dicionario(uni[i].arvore);
			printf("\n");
			flag = 1;
		}
	}
	return flag;
}

//busca palavra e imprime sua listas se emcontrada
void busca_palavra(arvorebin *Raiz, char str[50],int *flag){

	if (Raiz != NULL){
		
		if ( strcmp(str,Raiz->palavra) == 0){
			imprimir_lista_ingles(Raiz->l_ingles);
			*flag = 1;
		}
		
		else if (strcmp(str,Raiz->palavra) < 0)
			busca_palavra(Raiz->esq,str,flag);
		else
			busca_palavra(Raiz->dir,str,flag);
	}
}

//receve vetor de arvores e uma palavra em portugues e imprime todas as equivalentes em ingles
int imprimir_equivalentes_ingles(unidades uni[TAM],char str[30]){ 
	int i,flag=0;

	for (i = 0; i < TAM; ++i){
		busca_palavra(uni[i].arvore,str,&flag);
	}

	return flag;
}

void remover_lista(lista **l){

	lista *aux;

	while(*l != NULL){
		aux = *l;
		*l = (*l)->prox;

		free(aux);
	}
}

//recebe raiz e uma variavel do tipo arvore e devolve nesta variavel o endereço do no da raiz que possui o maior valor
void maior_valor(arvorebin *Raiz, arvorebin **maior){

	if (Raiz != NULL){

		if (Raiz->dir != NULL)
			maior_valor(Raiz->dir,maior);
		else
			*maior = Raiz;
	}
}

//recebe arvore e uma palavra e remove a palavra e sua lista e retorna 1 se a operação foi concluida
void remover(arvorebin **Raiz ,char str[50] ,int *flag){
	 
	if (*Raiz != NULL){

		if ( strcmp(str,(*Raiz)->palavra) == 0){
	//o valor da raiz é o no que queremos remover e Raiz_ant aponta para o No anterior do No que iramos remover

			arvorebin *aux = NULL;

			remover_lista(&(*Raiz)->l_ingles);  //remove todas palavras da lista 

			*flag = 1;

			if ((*Raiz)->esq == NULL && (*Raiz)->dir == NULL){

				aux = *Raiz;

				*Raiz = NULL;

				free(aux);
	
			}else if ((*Raiz)->esq != NULL && (*Raiz)->dir == NULL){ 

				aux = *Raiz;


				*Raiz = (*Raiz)->esq;

				free(aux);


	
			}else if ((*Raiz)->esq == NULL && (*Raiz)->dir != NULL){

					aux = *Raiz;

					*Raiz = (*Raiz)->dir;

					free(aux);
			
			}else{

				arvorebin *maior;			
			
				maior_valor((*Raiz)->esq,&maior); //busca o maior valor da esquerda e devolve na variavel maior

				aux = *Raiz;

				maior->dir = (*Raiz)->dir;

				*Raiz = (*Raiz)->esq;

				free(aux);
			}

										      			
		
		}else if( strcmp(str,(*Raiz)->palavra) < 0){  //busca o No que sera removido
		    
			remover(&(*Raiz)->esq,str,flag);				  

		}else{

			remover(&(*Raiz)->dir,str,flag);             
		}


		if (*Raiz != NULL){
			
			(*Raiz)->altura = altura_no(*Raiz);   //recalcula altura do No

			verifica_balanceamento(Raiz);       //verifica e se nescessario balanceia arvore
		}
	
	}
}

//receve vetor de arvores e o nome de uma unidade e uma palavra e busca e remove a palavra da arvore e sua lista
int remover_palavra(unidades uni[TAM],char unidade[30],char str[50]){
	
	int i,flag=0;
	char aux[30]="%";
	strcat(aux, unidade);

	for (i = 0; i < TAM; ++i){

		if (strncmp(uni[i].nome,aux,strlen(uni[i].nome)-1) == 0){

			remover(&uni[i].arvore,str,&flag);
			printf("\n");
		}
	}
	return flag;
}

void busca_palavra2(arvorebin *Raiz, char str[50],int *flag){

	if (Raiz != NULL){
		
		if ( strcmp(str,Raiz->palavra) == 0){
			*flag = 1;
		}
		
		else if (strcmp(str,Raiz->palavra) < 0)
			busca_palavra2(Raiz->esq,str,flag);
		else
			busca_palavra2(Raiz->dir,str,flag);
	}
}

//calulca o tempo de busca de uma senquencia de elementos
void calcula_tempo_busca(unidades uni[TAM],char str[50]){ 
	int i,flag=0;

	clock_t Ticks[2];

    Ticks[0] = clock();                                      

	for (i = 0; i < TAM; ++i){

		busca_palavra2(uni[i].arvore,str,&flag);
		
	}
	Ticks[1] = clock();

	printf("\nTempo busca palavra %s: %g ms.", str,calcula_tempo(Ticks));
}

int menu(){

	int op;
	
	printf("\n1- Imprimir palavras de uma unidade\n");
	printf("2- imprimir palavras em ingles equivalentes a uma em portugues\n");
	printf("3- Remover palavra em portugues e suas equivalentes em ingles\n");
	printf("4- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",&op);

	return op;
}

int main(){

	int op,n;

	FILE *file;

	unidades arvores[TAM];

	char unidade[30],str[50];


	open_file(&file,"ingles-portugues.txt");
	
	carrega_dados(file,arvores);
	
	calcula_tempo_busca(arvores,"poder");    


	do{
		
		op = menu();

		switch (op){

			case 1:

				printf("\ndigite o nome da unidade: ");
				scanf("%s",unidade);

				n = imprimir_unidade(arvores,unidade);

				if (n == 0){
					printf("\nUnidade buscada nao exite!!!\n");
				}

				break;

			case 2:

				printf("\ndigite a palavra em portugues: ");
				scanf("%s",unidade);

				n = imprimir_equivalentes_ingles(arvores,unidade);

				if (n == 0){
					printf("\nPalavra buscada nao exite!!!\n");
				}

				break;
			
			case 3:

				printf("\ndigite o nome da unidade: ");
				scanf("%s",unidade);

				printf("\ndigite a palavra em portugues: ");
				scanf("%s",str);

				n = remover_palavra(arvores,unidade,str);

				if (n == 0)
					printf("\nPalavra ou uinidade inexistente!!!\n");
				else
					printf("\nOperacao concluida!!\n");

				break;

			case 4:
				printf("\nSAINDO.........\n");
				break;
	

			
			
			default:
				printf("\nopcao invalida!!!\n");

				break;
			

		}


	}while(op != 4);
	


	return 0;
}