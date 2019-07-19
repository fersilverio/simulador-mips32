#ifndef ULA_H
#define ULA_H
#include <stdio.h>
#include <stdlib.h>

typedef struct alu{
    
    int operando1;  //valor de entrada
    int operando2;  //valor de entrada
    long long int saida_ula;    //valor de saida
    unsigned int ula_op;    //operação executada pela ula
}ula;

long long int ulaAdd();
void ulaSub();
void ulaAnd();
void ulaOr();
void ulaXor();

#endif

