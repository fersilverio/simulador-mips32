#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "includes/executionQueue.h"

struct exeQueue{
    char *instructionName;
    int imediato;
	char *regDestino, *reg1, *reg2;
    struct exeQueue *prox;
};

fila* create (){
	fila *F;
	F = (fila*) calloc(1,sizeof(fila));
	if(F != NULL){
		F->prox = NULL;
	}
	return F;
}

/*
fila *alocar(char *nome,int dado1, int dado2, int dest){
	fila *novo = (fila *) malloc(sizeof(fila));
	if(novo != NULL){
		strcpy(novo->instructionName,nome);
		novo->reg1 = dado1;
		novo->imediato = dado2;
		novo->regDestino = dest;
		novo->prox = NULL;
	}
	return novo;
}
*/
fila* alocarInst(char *nome){
	fila *novo = (fila *) malloc(sizeof(fila));
	if(novo != NULL){
		strcpy(novo->instructionName,nome);
		novo->prox = NULL;
	}
	return novo;
}

void alocarRegDest(fila *F, char *registrador){

	if(F != NULL){
		strcpy(F->regDestino, registrador);
	}

}

void alocarReg1(fila *F, char *registrador){

	if(F != NULL){
		strcpy(F->reg1, registrador);
	}

}

void alocarReg2(fila *F, char *registrador){

	if(F != NULL){
		strcpy(F->reg2, registrador);
	}

}

void alocarDado(fila *F, int dado){

	if(F != NULL){
		F->imediato = dado;
	}

}
/*
void queueIn(fila *F,char *nome,int dado1, int dado2, int dest){
	fila *novo = alocar(nome,dado1,dado2,dest);
	fila *aux;
	aux = F;
	while (aux->prox != NULL){
		aux = aux->prox;
	}
	aux->prox = novo;
}
*/
fila* queueInInst(fila *F,char *nome){

	fila *novo = alocarInst(nome);
	fila *aux;
	aux = F;
	while (aux->prox != NULL){
		aux = aux->prox;
	}
	aux->prox = novo;

	return novo;

}

fila* queueInRegDest(fila *novo, char* reg){

	alocarRegDest(novo, reg);
	return novo;

}

fila* queueInReg1(fila *novo, char* reg){
	
	alocarReg1(novo, reg);
	return novo;

}

fila* queueInReg2(fila *novo, char* reg){

	alocarReg2(novo, reg);
	return novo;

}

fila* queueInImediato(fila *novo, int imediato){

	alocarDado(novo, imediato);
	return novo;

}

fila queueOut (fila* F){
	fila *excluir;
	fila *saida;
	excluir = F->prox;
	if(excluir != NULL){
		F->prox = F->prox->prox;
		saida = excluir;
		free(excluir);
		return *saida;
	}
}

void clear(fila* F){
	fila *aux; 							
	aux = F;
	while(aux->prox != NULL){
		queueOut(F);
		aux->prox = aux->prox->prox;
	}
	free(F);
	F = NULL; 
}


void printQueue(fila *F){
	fila *aux;
	aux = F->prox;
	int k = 1;
	if(aux == NULL){
		printf("FIla vazia!\n");
	}
	else{
		printf("Inicio --> ");
		while(aux != NULL){
			printf("Posição da fila: %d => Nome: %s , reg1: %s , reg2: %s , ValorDestino: %s, imediato: %d \n",k,aux->instructionName,aux->reg1,aux->reg2,aux->regDestino, aux->imediato);
			aux = aux->prox;
			k++;
		}			
	}
}

void ler(){

    FILE* arq_asm = fopen("arq.asm", "r");
    FILE* saida = fopen("saida.txt", "w");

    char atual;

    atual = fgetc(arq_asm);

    while(atual != EOF){
            
        if(atual == ' ' || atual == ',' || atual == '\n')
            atual = fgetc(arq_asm);

        else if(atual == '$'){

            while((atual != ',') && (atual != '\n') && (atual != EOF)){

                fprintf(saida, "%c",atual);
                atual = fgetc(arq_asm);

            }

            fputs("\n", saida);

        }

        else{

            while(atual != ' '){

                fprintf(saida, "%c", atual);
                atual = fgetc(arq_asm);

            }

            fputs("\n", saida);
            atual = fgetc(arq_asm);

        }
    }

	fclose(saida);
    fclose(arq_asm);

}

void inserirElementos(){

	FILE *saida = fopen("saida.txt", "r");

	int i;
    char str[6];

	fila *fi = create();
	fila *novo;

    while(!feof(saida)){

        fgets(str, 6, saida);

        if(str[0] == '$'){
			
			//é um registrador destino ou operando
			//inserir str em fila->valor ou fila->regDestino
			i++;

			if(i == 1)
				queueInRegDest(novo, str);

			else if(i == 2)
				queueInReg1(novo, str);
			
			else
				queueInReg2(novo, str);	

		}
		
		else if(isdigit(str[0])){

			int valor = atoi(str);
			queueInImediato(novo, valor);

		}

		else{

			i = 0;
			novo = queueInInst(fi, str);

		}
		

    }

    fclose(saida);
}