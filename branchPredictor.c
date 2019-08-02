#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "includes/branchPredictor.h"
#include "includes/operationsUnit.h"
#include "includes/executionQueue.h"

/*
unsigned int toInt(char *num){
    unsigned int numero = atoi(num);
    return numero;

}
*/

bool prediction(char *instrucao, int a, int b){

    //int a = toInt(reg1);
    //int b = toInt(reg2);

    if(strcmp(instrucao,"beq\n") == 0 || strcmp(instrucao,"beql\n") == 0){
        if(a == b){
            return true;
        }
        else{
            return false;
        }
    }
    else if(strcmp(instrucao,"bne\n") == 0){
        if(a != b){
            return true;
        }
        else{
            return false;
        }
    }
    else if(strcmp(instrucao,"bgez\n") == 0){
        if(a >= 0){
            return true;
        }
        else{
            return false;
        }
    }
    else if(strcmp(instrucao,"bgtz\n") == 0){
        if(a > 0){
            return true;
        }
        else{
            return false;
        }
    }
    else if(strcmp(instrucao,"blez\n") == 0){
        if(a <= 0){
            return true;
        }
        else{
            return false;
        }
    }
    else if(strcmp(instrucao,"bltz\n") == 0){
        if(a < 0){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        printf("No branch instruction");
    }
}



bool isBranch(char* instrucao){
    if(strcmp(instrucao,"b\n") == 0 ||strcmp(instrucao,"beq\n") == 0 ||strcmp(instrucao,"beql\n") == 0 ||
      strcmp(instrucao,"bgez\n") == 0 ||strcmp(instrucao,"bgtz\n") == 0 ||strcmp(instrucao,"blez\n") == 0 ||
      strcmp(instrucao,"bltz\n") == 0 ||strcmp(instrucao,"bne\n") == 0){
        return true;
    }
    else{
        return false;
    }
}


struct numerosPrevisao previsao(char *instrucao, int reg1, int reg2){

    struct numerosPrevisao n;
    n.acertos = 0;
    n.erros = 0;
    
    bool previsao = prediction(instrucao, reg1, reg2);
    if(previsao == true){
        n.acertos++;
    }
    else{
        n.erros++;
    }
    
    return n;

}