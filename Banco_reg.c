#include <stdio.h>
#include <stdlib.h>
#include "head.h"

void print_regs(signed char reg[8])
{
    printf("\n--- REGISTRADORES ---\n");

    for(int i = 0; i < 8; i++)
    {

        printf("R%d = ", i);

        print_bin8((unsigned char)reg[i]);

        printf(" (%d)", reg[i]);

        printf("\n");

    }

    printf("---------------------\n");
}

int iniat(signed char reg[8])
{
    reg[0]=0; reg[1]=0; reg[2]=0; reg[3]=0;
    reg[4]=0; reg[5]=0; reg[6]=0; reg[7]=0;

    return 0;
}


int read(signed char reg[8], signed char A, signed char B, signed char *outA, signed char *outB)
{

    *outA = reg[A];

    *outB = reg[B];

    return 0;

}

int Rdest(int Sinais[8], signed char A, signed char B)
{

    return (Sinais[REG_DST]) ? A : B;

}

int esc(signed char reg[8], int dest, signed char A,int RegWrite)
{

    if(dest != 0 && RegWrite==1)
    {

        reg[dest] = A;

    }

    return 0;

}
