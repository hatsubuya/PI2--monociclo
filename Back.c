#include <stdio.h>
#include <stdlib.h>
#include "Head.h"


void push(Snapshot *pilha, int *sp,signed char reg[], int Sinais[], int ULAop,int overflow, int dest, signed char immx,unsigned char instruct, int n)
{

    if (*sp >= 500)
    {

        printf("\n pilha cheia! nao e possivel salvar mais estados");

        return;

    }

    (*sp)++;

    Snapshot *s = &pilha[*sp];

    for (int i = 0; i < 8; i++)
    {

        s->reg[i] = reg[i];

        s->Sinais[i] = Sinais[i];

    }

    s->ULAop = ULAop;

    s->overflow = overflow;

    s->dest = dest;

    s->immx = immx;

    s->instruct = instruct;

    s->n = n;

}

void pop(Snapshot *pilha, int *sp,signed char reg[], int Sinais[], int *ULAop,int *overflow, int *dest, signed char *immx,unsigned char *instruct, int *n)
{

    if (*sp < 0)
    {

        printf("\n nada para desfazer");

        return;
    }

    unsigned char pc_atual = *instruct;

    int instr_atual = *n;

    Snapshot *s = &pilha[*sp];

    (*sp)--;

    for (int i = 0; i < 8; i++)
    {

        reg[i] = s->reg[i];

        Sinais[i] = s->Sinais[i];

    }

    *ULAop = s->ULAop;

    *overflow = s->overflow;

    *dest = s->dest;

    *immx = s->immx;

    *instruct = s->instruct;

    *n = s->n;

    printf("Instrucao atual era: %d | PC: %d\n", instr_atual, pc_atual);

    printf("Voltou para instrucao: %d | PC: %d\n", *n, *instruct);

}
