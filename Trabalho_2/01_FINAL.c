#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h> //clock(), CLOCKS_PER_SEC e clock_t

#define Repeticoes 30 // Quantidade de Repeticoes para busca

typedef struct{

	int I_bloco,F_bloco;  //I_bloco= Inicio do Bloco ,F_bloco = Fim do bloco
	char estado;         // Estado do bloco ('o' = ocupado , 'l' = livre)

}bloco;
 
//Struct armazena os dados de cada nó
typedef struct b{

	bloco info1, info2;
	struct b *esq,*cen,*dir;
	int Ninfos;

}arvore23;


/*----------------------------------------------------------------------------------------------------------------------------------------------*/
											/*FUNÇÕES PADRÃO ARVORE 23*/

int ehfolha(arvore23 *No){ // FUNÇÃO PARA VERIFICAR SE O NÓ É FOLHA

	int flag = 0;

	if (No != NULL){
		if (No->esq == NULL && No->cen == NULL && No->dir == NULL)
			flag = 1;
	}
	
	return flag;
}

// Recebe um No e uma info e cria um novo No
void criaNo(arvore23 **No, bloco info, arvore23 *esq, arvore23 *cen ){

	*No = (arvore23 *)malloc(sizeof(arvore23));

	(*No)->info1 = info;
	(*No)->Ninfos = 1;
	(*No)->esq = esq;
	(*No)->cen = cen;
	(*No)->dir = NULL;
}

//Quando o No tem espaço adiciona a info no No, filho pode ser NULL ou ele sera o No com maior info apos a quebra de um No
void adicionaNo(arvore23 **No, bloco info, arvore23 *filho){

	if (info.I_bloco > (*No)->info1.I_bloco ){ 
		(*No)->info2 = info;
		(*No)->dir = filho;
		
	//caso em que a info é menor que a info1 do No
	}else{

		(*No)->info2 = (*No)->info1;
		(*No)->info1 = info;
		(*No)->dir = (*No)->cen;
		(*No)->cen = filho;
	}

	(*No)->Ninfos = 2;
}

//Recebe um No e uma info e um filho que pode ser NULL ou nao e devolve na variavel sobe: No_Maior (No criado com  maior info) e o que fica e o No com a menor info
void quebraNo(arvore23 **No,bloco info, bloco *sobe, arvore23 **No_maior,  arvore23 *filho){

	if (info.I_bloco < (*No)->info1.I_bloco ){ // o do meio é a info1
		
		*sobe = (*No)->info1;
		(*No)->info1 = info;
		criaNo(No_maior,(*No)->info2,(*No)->cen,(*No)->dir);
		(*No)->cen = filho;
		

	}else if (info.I_bloco < (*No)->info2.I_bloco ){ // o do meio é a info

		*sobe = info; 
		criaNo(No_maior,(*No)->info2,filho,(*No)->dir); //modificação
	

	}else{

		*sobe = (*No)->info2;
		criaNo(No_maior,info,(*No)->dir,filho);
	}

	(*No)->dir = NULL;
	(*No)->Ninfos = 1;
}

//Libera memoria alocada de um No (remove o No)
void libera_No(arvore23 **No){

	arvore23 *aux;

	aux = *No;
	*No = NULL;
	free(aux);
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------------------------------------------------------*/
											/* FUNÇÕES PARA REALIZAR A REMOÇÃO DOS BLOCOS*/

//Recebe um No Folha e o seu Pai e remove quando No é esquerda do Pai
int remove_esq_folha(arvore23 **Raiz,arvore23 **pai){
												
	int flag = 0;

	(**Raiz).info1 = (**pai).info1;	
		
	if((**pai).cen->Ninfos == 2){

		(**pai).info1 = (**pai).cen->info1;
		(**pai).cen->info1 = (**pai).cen->info2;
		(**pai).cen->Ninfos = 1;

	}else if((**pai).Ninfos == 2){

		(**pai).info1 = (**pai).cen->info1;
		(**pai).cen->info1 = (**pai).info2;
		
		if ((**pai).dir->Ninfos == 2){

			(**pai).info2 = (**pai).dir->info1;
			(**pai).dir->info1 = (**pai).dir->info2;
			(**pai).dir->Ninfos = 1;
		
		}else{

			adicionaNo(&(**pai).cen,(**pai).dir->info1,NULL);
			libera_No(&(**pai).dir);
	       	(**pai).Ninfos = 1;
		}

	//caso em que o pai e seus filhos so tem uma info, entao ao remover o valor a arvore fica desbalanceada	
	}else{

		adicionaNo(pai,(**pai).cen->info1,NULL);

		(**pai).Ninfos = 2;

		libera_No(&(**pai).esq);
		libera_No(&(**pai).cen);
		flag = 1;
	}

	//retorna 0 se ao remover a arvore nao foi desbalanceada, retorna 1 se foi desbalanceada
	return flag; 
}

//Recebe um No Folha e o seu pai, remove quando o No é o centro do pai
int remove_centro_folha(arvore23 **Raiz,arvore23 **pai){

	int flag = 0;
	
	if((**pai).esq->Ninfos == 2){

		(**Raiz).info1 = (**pai).info1;
		(**pai).info1 = (**pai).esq->info2;
		(**pai).esq->Ninfos = 1;
				

	}else if((**pai).Ninfos == 2 ){

		(**Raiz).info1 = (**pai).info2;
								
		if ((**pai).dir->Ninfos == 2){

			(**pai).info2 = (**pai).dir->info1;
			(**pai).dir->info1 = (**pai).dir->info2;
			(**pai).dir->Ninfos = 1;
		}else{

			adicionaNo(&(**pai).cen,(**pai).dir->info1,NULL);
			libera_No(&(**pai).dir);
	       	(**pai).Ninfos = 1;
		}
	
	//caso em que o pai e seus filhos so tem uma info, entao a ao remover o valor a arvore fica desbalanceada
	}else{

		adicionaNo(pai,(**pai).esq->info1,NULL);

		(**pai).Ninfos = 2;

		libera_No(&(**pai).esq);
		libera_No(&(**pai).dir);
		flag = 1;

	}
	//retorna 0 se ao remover a arvore nao foi desbalanceada, retorna 1 se foi desbalanceada
	return flag; 
}

//Recebe um No folha e o seu pai, remove quando o No é a direita do Pai
void remove_dir_folha(arvore23 **Raiz,arvore23 **pai){

	(**Raiz).info1 = (**pai).info2;
	
	if((**pai).cen->Ninfos == 2){

		(**pai).info2 = (**pai).cen->info2;
		(**pai).cen->Ninfos = 1;

	}else if((**pai).esq->Ninfos == 2){

		bloco aux = (**pai).cen->info1;
		
		(**pai).cen->info1 = (**pai).info1;
		(**pai).info1 = (**pai).esq->info2;
		(**pai).info2= aux;
		(**pai).esq->Ninfos = 1;
	
	}else{

		adicionaNo(&(**pai).cen,(**pai).info2,NULL);
		(**pai).Ninfos = 1;
		libera_No(&(**pai).dir);
	}

}

//Remove o No quando é folha, recebe o No que vai ter seu valor removido e o No Pai, depois remove o No
int remove_folha(arvore23 **Pai,arvore23 **Raiz, int bloco_I){

	int balanceamento = 0;

	if ((*Raiz)->Ninfos == 2){
					
		if ( bloco_I == (*Raiz)->info1.I_bloco){
			(*Raiz)->info1 = (*Raiz)->info2;
		}

		(*Raiz)->Ninfos = 1;
				
	}else if (*Pai == NULL){
		libera_No(Raiz);	
				
	}else{

		if (*Raiz == (**Pai).esq)
			balanceamento = remove_esq_folha(Raiz,Pai);

		else if (*Raiz == (**Pai).cen)
			balanceamento = remove_centro_folha(Raiz,Pai);

		else if (*Raiz == (**Pai).dir)
			remove_dir_folha(Raiz,Pai);
	}

	return balanceamento;
}

//Recebe o No e a Info, remove o valor do No quando os filhos do No são folhas
int remove_NoFilhos_folhas(arvore23 **Raiz ,int info){

	int balanceamento = 0;

	if(info == (**Raiz).info1.I_bloco){ //remove quando a info é a info1 do No
		
		if((**Raiz).cen->Ninfos == 2){

			(**Raiz).info1 = (**Raiz).cen->info1;
			(**Raiz).cen->info1 = (**Raiz).cen->info2;
		   	(**Raiz).cen->Ninfos = 1;

		}else if((**Raiz).esq->Ninfos == 2){

			(**Raiz).info1 = (**Raiz).esq->info2;
   			(**Raiz).esq->Ninfos = 1;


		}else if((**Raiz).Ninfos ==2){

				(**Raiz).info1 = (**Raiz).cen->info1;
				(**Raiz).cen->info1 = (**Raiz).info2;
				
			if((**Raiz).dir->Ninfos == 2 ){

				(**Raiz).info2 = (**Raiz).dir->info1;
				(**Raiz).dir->info1 =(**Raiz).dir->info2;
				(**Raiz).dir->Ninfos = 1;

			}else{
				adicionaNo(&(**Raiz).cen,(**Raiz).dir->info1,NULL);
				(**Raiz).Ninfos = 1;
				libera_No(&(**Raiz).dir);
			}

		//caso em que o pai e seus filhos so tem uma info, entao ao remover o valor a arvore fica desbalanceada
		}else{ 	 
		  		

			arvore23 *aux;

			adicionaNo(&(**Raiz).esq,(**Raiz).cen->info1,NULL);
			aux = (**Raiz).esq;
			libera_No(&(**Raiz).cen);
			libera_No(Raiz);
			*Raiz = aux;
			balanceamento = 1;
		}

	//remove quando a info é a info2 do No
	}else{

		if((**Raiz).dir->Ninfos == 2){

			(**Raiz).info2 = (**Raiz).dir->info1;
			(**Raiz).dir->info1=  (**Raiz).dir->info2;
			(**Raiz).dir->Ninfos = 1;

		}
		else if((**Raiz).cen->Ninfos == 2){

			(**Raiz).info2 = (**Raiz).cen->info2;
		   	(**Raiz).cen->Ninfos = 1;

		}
		else if((**Raiz).esq->Ninfos == 2){

			(**Raiz).info2 = (**Raiz).cen->info1;
		   	(**Raiz).cen->info1 = (**Raiz).info1;
		   	(**Raiz).info1 = (**Raiz).esq->info2;
		   	(**Raiz).esq->Ninfos = 1;

		}
		else{

			adicionaNo(&(**Raiz).cen,(**Raiz).dir->info1,NULL);
			(**Raiz).Ninfos = 1;
			libera_No(&(**Raiz).dir);

		}
	}
	//retorna 0 se ao remover a arvore nao foi desbalanceada, retorna 1 se foi desbalanceada
	return balanceamento; 
						 
}

//Recebe um No e um valor para balanceiaArvore, ver em que lado da raiz esta desbalanceado entao balanceia o No
int balanceiaArvore(arvore23 **Raiz, int desbalanceamento){ 

	bloco sobe;
	arvore23 *No_maior;
	arvore23 *aux;

	if (desbalanceamento == -1){ //quando o desbalanceamento está para a esquerda da raiz

		aux = (*Raiz)->cen->esq;
		(*Raiz)->cen->esq = (*Raiz)->esq;
		
		if((*Raiz)->cen->Ninfos == 1){

			adicionaNo(&(*Raiz)->cen,(*Raiz)->info1,aux);
			(*Raiz)->esq = NULL;
			
			if((*Raiz)->Ninfos == 1){

				aux = *Raiz;
				*Raiz = (*Raiz)->cen;
				libera_No(&aux);

			}else{

				(*Raiz)->info1 = (*Raiz)->info2;
				(*Raiz)->esq = (*Raiz)->cen;
				(*Raiz)->cen = (*Raiz)->dir;
				(*Raiz)->dir = NULL;
				(*Raiz)->Ninfos = 1;
			}
			
		}else{

			quebraNo(&(*Raiz)->cen,(*Raiz)->info1,&sobe,&No_maior,aux);
			(*Raiz)->info1 = sobe;
			(*Raiz)->esq = (*Raiz)->cen;
			(*Raiz)->cen = No_maior;
		}

	}else if (desbalanceamento == 0){ //quando o desbalanceamento está para o centro da raiz

		if((*Raiz)->esq->Ninfos == 1){

			adicionaNo(&(*Raiz)->esq,(*Raiz)->info1,(*Raiz)->cen);
			(*Raiz)->cen = NULL;
			
			if((*Raiz)->Ninfos == 1){
				
				aux = *Raiz;
				*Raiz = (*Raiz)->esq;
				libera_No(&aux);

			}else{

				(*Raiz)->info1 = (*Raiz)->info2;
				(*Raiz)->cen = (*Raiz)->dir;
				(*Raiz)->dir = NULL;
				(*Raiz)->Ninfos = 1;
			}
			
		}else{
			quebraNo(&(*Raiz)->esq,(*Raiz)->info1,&sobe,&No_maior,(*Raiz)->cen);
			(*Raiz)->info1 = sobe;
			(*Raiz)->cen = No_maior;
		}
		
	}else{ //quando o desbalanceamento está para direita da raiz
		
		if((*Raiz)->cen->Ninfos == 1){
			adicionaNo(&(*Raiz)->cen,(*Raiz)->info2,(*Raiz)->dir);
			(*Raiz)->Ninfos = 1;
			(*Raiz)->dir = NULL;

		}else{

			quebraNo(&(*Raiz)->cen,(*Raiz)->info2,&sobe,&No_maior,(*Raiz)->dir);
			(*Raiz)->info2 = sobe;
			(*Raiz)->dir = No_maior;
		}
	}
	return 0;

}

//FUNÇÃO QUE RECEBE UM NO E PERCORRE A PARTIR DELE BUSCANDO A MENOR INFORMAÇÃO PARA REMOVER E RETORNAR NA VARIAVEL info_sobe
int remove_MenorNo(arvore23 **pai_aux,arvore23 **No,bloco *info_sobe){
	int balanceamento = 0;

	if ((*No)->esq != NULL){

		balanceamento = remove_MenorNo(No,&(*No)->esq,info_sobe);
	
	}else{
		*info_sobe = (*No)->info1;
		balanceamento = remove_folha(pai_aux,No,(*No)->info1.I_bloco);
	}
	return balanceamento;
}

/*  remover recebe a Raiz o pai que incia com NULL a info que desejamos remover e flag
    a remoção pode ser feita atravez de 3 casos
   
    1- se o No é folha
   
    2- se os filhos do No são folhas

    3- se os filhos do No não são folhas, nesse caso é buscado o menor info da direita
    da info que queremos remover e fazemos com que a info que queremos remover receba 
    a menor info da sua direita;

    apos a remoção da info a arvore pode ter ficado desbalanceado, entao se o valor
    da variavel balanceamento for 1, quer dizer que teremos que balancear o No,
	então é chamada a funçao balanceiaArvore para isso
*/

int remover(arvore23 **Pai,arvore23 **Raiz ,int info, int *flag){ 

	int balanceamento = 0;

	if(*Raiz != NULL){

		if ( ((*Raiz)->info1.I_bloco == info ) || ((*Raiz)->Ninfos == 2 && (*Raiz)->info2.I_bloco == info)){
			*flag = 1;

			if (ehfolha(*Raiz) == 1){
				balanceamento = remove_folha(Pai,Raiz,info);
			
			}else if( (ehfolha((*Raiz)->esq) == 1 && ehfolha((*Raiz)->cen) == 1 && ehfolha((*Raiz)->dir) == 1) || (ehfolha((*Raiz)->esq) == 1 && ehfolha((*Raiz)->cen) == 1 && (*Raiz)->Ninfos == 1)){
				balanceamento = remove_NoFilhos_folhas(Raiz,info);
			
			}else{

				arvore23 *pai_aux = NULL;
				bloco info_sobe;
				
				if ((*Raiz)->info1.I_bloco == info){

					balanceamento = remove_MenorNo(&pai_aux,&(*Raiz)->cen,&info_sobe);
					(*Raiz)->info1 = info_sobe;

					if (balanceamento == 1){ //arvore foi desbalanceada para o centro
						balanceamento = balanceiaArvore(Raiz,0);
					}

				}else{

					balanceamento = remove_MenorNo(&pai_aux,&(*Raiz)->dir,&info_sobe);
					(*Raiz)->info2 = info_sobe;

					if (balanceamento == 1){//arvore foi desbalanceada para a direita
						balanceamento = balanceiaArvore(Raiz,1);
					}
				}
			}
				
		}else if( info < (*Raiz)->info1.I_bloco )
	        balanceamento = remover(Raiz,&(*Raiz)->esq,info,flag);
	        
		else if(  (*Raiz)->Ninfos == 2 && info > (*Raiz)->info2.I_bloco )
	        balanceamento = remover(Raiz,&(*Raiz)->dir,info,flag);
	    
	    else
	        balanceamento = remover(Raiz,&(*Raiz)->cen,info,flag);

	    if (balanceamento == 1 && *Raiz != NULL && *Pai != NULL){

	    	if (*Raiz == (**Pai).esq)
				balanceamento = balanceiaArvore(Pai,-1);
	    	else if (*Raiz == (**Pai).cen)
				balanceamento = balanceiaArvore(Pai,0);
			else if (*Raiz == (**Pai).dir)
				balanceamento = balanceiaArvore(Pai,1);
	    }
	}

	return balanceamento;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------------------------------------------------------*/
//FUNÇÃO PARA IMPRIMIR O BLOCO E SEUS RESPECTIVO ESTADO
void imprime_bloco_info(bloco b){

	printf("bloco: %d , %d -%c\n",b.I_bloco,b.F_bloco,b.estado);
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/* FUNÇÕES PARA BUSCAR OS VALORES NA ARVORE*/

//Recebe um No e percorre a partir desse No e retorna o No com a Menor info
struct b* busca_MenorNo(arvore23 **No){

	arvore23 *aux;													  

	if ((*No)->esq != NULL)
		aux = busca_MenorNo(&(*No)->esq);
	else
		aux = *No;

	return aux;
}

//Recebe um No e percorre a partir desse No e retorna o No com a Maior info
struct b* busca_MaiorNo(arvore23 **No){

	arvore23 *aux;													  

	if ((*No)->cen != NULL)
		aux = busca_MenorNo(&(*No)->cen);
	else
		aux = *No;

	return aux;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------------------------------------------------------*/
								/*FUNÇÃO PARA JUNTAR INFORMAÇÕES APÓS OCUPAR ESPAÇO*/

//Recebe o Pai e a Raiz com a info que queremos ocupar, ocupando a quantidade exata de info e entao concatenamos as infos
void concatenaInfo(arvore23 **Raiz,arvore23 **Pai){

	int flag = 0,aux;

	//caso em que a Raiz esta entre um No ocupado e um livre, concatena raiz com a info1 do pai e remove a Raiz

	if ((*Raiz)->Ninfos == 1){
								
		if ((*Pai)->esq == *Raiz){

			(*Pai)->info1.I_bloco = (*Raiz)->info1.I_bloco;
			remover(Pai,Raiz,(*Raiz)->info1.I_bloco,&flag); 

										 
		//caso em que a Raiz esta entre um No ocupado e um livre, concatena raiz com a info2 do pai e remove a Raiz
		}else if ((*Pai)->dir == *Raiz){

			(*Pai)->info2.F_bloco = (*Raiz)->info1.F_bloco;
			remover(Pai,Raiz,(*Raiz)->info1.I_bloco,&flag); 
		
		//caso em que a Raiz esta entre duas infos ocupadas, concatena raiz com a info1 e a info2 do pai e remove a Raiz  e a info2 do pai
		}else{
									
			if ((*Pai)->Ninfos == 2){
				
				(*Pai)->info1.F_bloco = (*Pai)->info2.F_bloco;
				
				aux = (*Pai)->info2.I_bloco;

				remover(Pai,Raiz,(*Raiz)->info1.I_bloco,&flag);	
				remover(Pai,Raiz,aux,&flag);	
			
			}
		}
	
	//quando a Raiz possui 2 infos, entao a info que queremos ocupar esta entre duas infos ocupadas, concatenamos com a info do pai e removemos a Raiz
	}else{   
		
		if((*Pai)->cen == *Raiz){

			(*Pai)->info1.F_bloco = (*Raiz)->info2.F_bloco;
		}else{
			(*Pai)->info2.F_bloco = (*Raiz)->info2.F_bloco;
		}

		remover(Pai,Raiz,(*Raiz)->info2.I_bloco,&flag);
		remover(Pai,Raiz,(*Raiz)->info1.I_bloco,&flag);
	}
}

/*FUNÇÃO PARA OCUPAR ESPAÇOS LIVRE NA MEMORIA*/
void ocupa_espaco(arvore23 **Pai ,arvore23 **Raiz, int Tam_bloco, int *flag){
   
	if(*Raiz != NULL && *flag != 1 ){
		
		//caso em que o bloco livre encontrado possui mais espaço do que o desejado sendo a info 1 do N0
		if ( (*Raiz)->info1.estado == 'l' && ((*Raiz)->info1.F_bloco - (*Raiz)->info1.I_bloco +1) > Tam_bloco){
			*flag = 1;
			if (ehfolha(*Raiz) == 1){
				
				//caso em que é a Raiz da arvore e so tem uma info
				if ((*Raiz)->Ninfos == 1 && *Pai == NULL){

					(*Raiz)->info2.F_bloco = (*Raiz)->info1.F_bloco;
					(*Raiz)->info1.F_bloco -= Tam_bloco;
					(*Raiz)->info2.I_bloco = (*Raiz)->info1.F_bloco + 1;
					(*Raiz)->info2.estado = 'o';
					(*Raiz)->Ninfos = 2;
					
				}else if ((*Raiz)->Ninfos == 2){

					(*Raiz)->info1.F_bloco -= Tam_bloco;
					(*Raiz)->info2.I_bloco = (*Raiz)->info1.F_bloco + 1; 
				
				}else{
					
					if ((*Raiz)->info1.I_bloco < (*Pai)->info1.I_bloco ){
						(*Raiz)->info1.F_bloco -= Tam_bloco;
						(*Pai)->info1.I_bloco = (*Raiz)->info1.F_bloco + 1;

					}else{
						(*Raiz)->info1.I_bloco += Tam_bloco;

						if((*Raiz) == (*Pai)->cen) 
							(*Pai)->info1.F_bloco += Tam_bloco;	
						else
							(*Pai)->info2.F_bloco += Tam_bloco;;
					
					}
				}
			
			}else{

				arvore23 *aux;

				(*Raiz)->info1.F_bloco -= Tam_bloco;
				aux = busca_MenorNo(&(*Raiz)->cen);
				aux->info1.I_bloco = (*Raiz)->info1.F_bloco + 1;
			}

		//caso em que o bloco livre encontrado e possui exatamente o espaço do que o desejado e é a info1 do No
		}else if ( (*Raiz)->info1.estado == 'l' && ((*Raiz)->info1.F_bloco - (*Raiz)->info1.I_bloco + 1) == Tam_bloco){

			*flag = 1;
				
			if (ehfolha(*Raiz) == 1){

				//caso em que é a Raiz da arvore
				if (*Pai == NULL){

					if ((*Raiz)->Ninfos == 2){
						(*Raiz)->info2.I_bloco = (*Raiz)->info1.I_bloco;
						(*Raiz)->info1 = (*Raiz)->info2;
						(*Raiz)->Ninfos = 1;
						
					}else
						(*Raiz)->info1.estado = 'o';
					 
				}else
					concatenaInfo(Raiz,Pai);
			
			//caso em que o No livre esta entre os ocupados e o No livre nao é folha, entao concatenamos os nos
			}else{

				arvore23 *maior,*menor;

				maior = busca_MaiorNo(&(*Raiz)->esq); //busca o maior No da esquerda
				menor = busca_MenorNo(&(*Raiz)->cen); //busca o menor No do cento

				maior->info1.F_bloco = menor->info1.F_bloco; //concatena os Nos

				remover(Pai,Raiz,menor->info1.I_bloco,flag);
				remover(Pai,Raiz,(*Raiz)->info1.I_bloco,flag);

			}
		
		//caso em que o bloco livre encontrado e possui mais espaço do que o desejado e é a info2 do No
		}else if ( (*Raiz)->Ninfos == 2 && (*Raiz)->info2.estado == 'l' && ((*Raiz)->info2.F_bloco - (*Raiz)->info2.I_bloco + 1) > Tam_bloco){ 

			*flag = 1;																													
			
			if(ehfolha(*Raiz) == 1)
			{
				(*Raiz)->info2.I_bloco += Tam_bloco;
				(*Raiz)->info1.F_bloco += Tam_bloco;
			
			}else{
				arvore23 *aux;

				(*Raiz)->info2.F_bloco -= Tam_bloco;
				
				aux = busca_MenorNo(&(*Raiz)->dir);

				aux->info1.I_bloco = (*Raiz)->info2.F_bloco + 1;
			}

		}else if ( (*Raiz)->Ninfos == 2 && (*Raiz)->info2.estado == 'l' && ((*Raiz)->info2.F_bloco - (*Raiz)->info2.I_bloco + 1) == Tam_bloco){
			*flag = 1;

			if (ehfolha(*Raiz) == 1){

				(*Raiz)->info1.F_bloco = (*Raiz)->info2.F_bloco;
				(*Raiz)->Ninfos = 1;

			//caso em que o No livre esta entre os ocupados e o No livre nao é folha, entao concatenamos os nos		
			}else{

				arvore23 *maior,*menor;

				maior = busca_MaiorNo(&(*Raiz)->cen); //busca o maior No do centro
				menor = busca_MenorNo(&(*Raiz)->dir); //busca o menor No do direita

				maior->info1.F_bloco = menor->info1.F_bloco; //concatena os Nos

				remover(Pai,Raiz,menor->info1.I_bloco,flag);
				remover(Pai,Raiz,(*Raiz)->info2.I_bloco,flag);
		
			}

		}else{

			ocupa_espaco(Raiz,&(*Raiz)->esq,Tam_bloco,flag);
			ocupa_espaco(Raiz,&(*Raiz)->cen,Tam_bloco,flag);
			ocupa_espaco(Raiz,&(*Raiz)->dir,Tam_bloco,flag);

		}		
	}
}


/*----------------------------------------------------------------------------------------------------------------------------------------------*/


//FUNÇÃO PARA LIMPAR O BUFFER
void limpa_buffer(){ 
	int ch;
	while((ch = fgetc(stdin)) != EOF && ch != '\n' ){}

}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
									/* FUNÇÕES PARA REALIZAR A INSERÇÃO NA ARVORE*/

//FUNÇÃO PARA INSERIR UMA NOVA INFO NA ARVORE
struct b* insere(arvore23 **Pai,arvore23 **Raiz ,bloco info, bloco *sobe){ 

	arvore23 *No_maior;
	No_maior = NULL;

	if (*Raiz == NULL){
		criaNo(Raiz,info,NULL,NULL);

	}else{

		if (ehfolha(*Raiz) == 1){
			
			if ((*Raiz)->Ninfos == 1){
				adicionaNo(Raiz,info,NULL);
			
			}else{

				quebraNo(Raiz,info,sobe,&No_maior,NULL);

				if (*Pai == NULL){
					arvore23 *aux;
					criaNo(&aux,*sobe,*Raiz,No_maior);

					*Raiz = aux;

					No_maior = NULL;
				}
			}
		
		}else {

			if (info.I_bloco < (*Raiz)->info1.I_bloco ){
			    No_maior= insere(Raiz,&(*Raiz)->esq,info,sobe);
			
		    }else if ((*Raiz)->Ninfos == 2 && info.I_bloco > (*Raiz)->info2.I_bloco){
			    No_maior= insere(Raiz,&(*Raiz)->dir,info,sobe);
		   	
		   	}else{
			    No_maior= insere(Raiz,&(*Raiz)->cen,info,sobe);
		    }

			if (No_maior != NULL){

				if ((*Raiz)->Ninfos == 1){
					adicionaNo(Raiz,*sobe,No_maior);			
					No_maior = NULL;
					
				}else{

					bloco sobe2;
					arvore23 *No_maior2;

					quebraNo(Raiz,*sobe,&sobe2,&No_maior2,No_maior);

					if (*Pai == NULL){
						arvore23 *aux;

						criaNo(&aux,sobe2,*Raiz,No_maior2);
						*Raiz = aux;
						No_maior = NULL;
					
					}else{
						*sobe = sobe2;
						No_maior= No_maior2;
					}
				}
			}
		}
	}

	return No_maior;
}


// RECEBE O TAMANHO DO BLOCO DETERMINADO PELO USUÁRIO E CHAMA A FUNÇÃO insere PARA INSERIR NA ARVORE
void insere_bloco_NaMemoria(arvore23 **Raiz, int quant_blocos){

	bloco info,sobe;
	arvore23 *Pai;

	info.I_bloco = info.F_bloco = 0;

	limpa_buffer();
	printf("digite o estado do primeiro bloco da memoria(l = livre ||  o = ocupado): ");
	scanf("%c",&info.estado);
	limpa_buffer();

	info.estado = tolower(info.estado);

	while(info.estado != 'o' && info.estado != 'l' ){
		printf("\ndigite um estado valido || (l = livre ||  o = ocupado)!!\n");
		printf("digite o estado do primeiro bloco da memoria(l = livre ||  o = ocupado): ");
		scanf("%c",&info.estado);
		info.estado = tolower(info.estado);
		limpa_buffer();

	}

	while(info.F_bloco < quant_blocos-1){

		Pai = NULL;
		printf("Espaco disponivel : %d Mb",quant_blocos -info.I_bloco );
		printf("\ninicio do bloco: %d\n",info.I_bloco);
		printf("digite o fim do bloco: ");
		scanf("%d",&info.F_bloco);
		printf("\n");

		while(info.F_bloco >= quant_blocos || info.F_bloco < info.I_bloco ){
			
			printf("\nValor invalido\n");
			printf("digite um valor valido para o fim do bloco(Espaco disponivel: %d Mb): ",quant_blocos -info.I_bloco);
			scanf("%d",&info.F_bloco);
		}

		insere(&Pai,Raiz,info,&sobe);

		info.I_bloco = info.F_bloco + 1;

		if (info.estado == 'l')
			info.estado = 'o';
		else 
			info.estado = 'l';

	}
}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/




/*----------------------------------------------------------------------------------------------------------------------------------------------*/
									/*FUNÇÃO PARA IMPRIMIR A ARVORE COMPLETA*/
void imprimir(arvore23 *Raiz){

	if(Raiz != NULL){

		imprimir(Raiz->esq);
		imprime_bloco_info(Raiz->info1);
		imprimir(Raiz->cen);

		if(Raiz->Ninfos == 2){
			imprime_bloco_info(Raiz->info2);
		}
		imprimir(Raiz->dir);
	}
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
int buscaArv23(arvore23 *Raiz, int chave) {
    int achou = 0;
    
    if (Raiz != NULL) { 
        
    
		if (ehfolha(Raiz) == 1) { // verifica se é uma folha
			if (Raiz->Ninfos == 1) { // verifica se tem apenas uma info
				if (chave >= Raiz->info1.I_bloco && chave <= Raiz->info1.F_bloco) { // verifica se a chave está dentro do intervalo do bloco da info1
					printf("esta no bloco %d - %d\n",Raiz->info1.I_bloco,Raiz->info1.F_bloco);
					achou = 1;
				}
			}
			else { // tem duas infos
				if (chave >= Raiz->info1.I_bloco && chave <= Raiz->info1.F_bloco) { // verifica se a chave está dentro do intervalo do bloco da info1
					printf("esta no bloco %d - %d\n",Raiz->info1.I_bloco,Raiz->info1.F_bloco);
					achou = 1;
				}
				else if (chave >= Raiz->info2.I_bloco && chave <= Raiz->info2.F_bloco) { // verifica se a chave está dentro do intervalo do bloco da info2
					printf("esta no bloco %d - %d\n",Raiz->info2.I_bloco,Raiz->info2.F_bloco);
					achou = 1;
				}
			}
		}
		else if (Raiz->Ninfos == 2) { // verifica se é um nó com um filho central
			if (chave < Raiz->info1.I_bloco) { // verifica se a chave é menor que a primeira chave
				achou = buscaArv23(Raiz->esq, chave); // busca na subárvore esquerda
			}
			else { // caso contrário
				achou = buscaArv23(Raiz->dir, chave); // busca na subárvore direita
			}
		}
		else { // caso contrário, é um nó com dois filhos centrais
			if (chave < Raiz->info1.I_bloco) { // verifica se a chave é menor que a primeira chave
				achou = buscaArv23(Raiz->esq, chave); // busca na subárvore esquerda
			}
			else if (chave > Raiz->info2.F_bloco) { // verifica se a chave é maior que a segunda chave
				achou = buscaArv23(Raiz->dir, chave); // busca na subárvore direita
			}
			else { // caso contrário, a chave está entre a primeira e a segunda chave
				achou = buscaArv23(Raiz->cen, chave); // busca na subárvore central
			}
		}
	}	
    return achou;
}



int main(){
	
	arvore23 *Raiz = NULL,*Pai;
	
	int op,n,flag,quant_blocos;
	double tempo_busca_total, tempo_insere_total;
	clock_t inicio,fim;

	printf("\ndigite o tamanho total da memoria em Mb: ");
	scanf("%d",&quant_blocos);

	while(quant_blocos <= 0){
		printf("\nNao existe memoria com tamanho igual ou menor que 0!!\n");
		printf("\ndigite o tamanho total da memoria em Mb acima de 0: ");
		scanf("%d",&quant_blocos);
	}

	inicio = clock();

	insere_bloco_NaMemoria(&Raiz,quant_blocos);

	fim = clock();

	tempo_insere_total = (double)(fim-inicio) / (CLOCKS_PER_SEC/1000000.0);

	do{
		
		printf("1- Imprime Blocos\n");
		printf("2- Ocupar blocos livre \n");
		printf("3- Sair \n");
		printf("\ndigite uma das opcoes: ");
		scanf("%d",&op);

		switch (op){

			case 1:
				
				imprimir(Raiz);
				break;

			case 2:

				flag = 0;
				Pai = NULL;
				
				printf("\ndigite o tamanho do bloco que voce deseja ocupar: ");
				scanf("%d",&n);

				while(n <= 0){
					printf("Valor nao pode ser menor ou igual a 0!!\n");
					printf("\nDigite um tamanho valido a ser ocupado: ");
					scanf("%d",&n);
				}

				ocupa_espaco(&Pai,&Raiz,n,&flag);

				if (flag == 0){
					printf("\nTamanho de bloco indisponivel!!\nImpossivel alocar essa quantidade de blocos!!\n");
				}else{
					printf("\nOperacao concluida!!\n");
				}
				break;

			case 3:

				inicio = clock();

				for(int x = 0; x < Repeticoes; x++){
					buscaArv23(Raiz,x*2);
				}
				fim = clock();
				tempo_busca_total = (double)(fim-inicio) / (CLOCKS_PER_SEC/1000000.0);

				printf("Tempo Medio de Busca %.2f microssegundos\n",tempo_busca_total/Repeticoes);
				printf("Tempo Insercao %.2f microssegundos\n",tempo_insere_total);

				printf("\nFinalizando Execucao do Sistema\n");
				break;		
	
			default:

				printf("\nOpcao Invalida!!!\n");
				break;
		}
		
	}while(op != 3);
	return 0;
}