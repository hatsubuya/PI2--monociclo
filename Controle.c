#include <stdio.h>
#include <stdlib.h>
#include "Head.h"


void Decodifica(unsigned char opcode, int Sinais[8])
{
    for(int i=0;i<8;i++)
    {

        Sinais[i]=0;

    }


    if(opcode == 0x0)
    {
        printf("Type R");

        //6
        Sinais[REG_DST]=1;

        Sinais[REG_WRITE]=1;

    }
    else if(opcode == 0x4)
    {

        printf("addi \n");

        Sinais[ALU_SRC]=1;

        Sinais[REG_WRITE]=1;


    }
    else if(opcode == 0xB)
    {
        printf("lw");

        Sinais[ALU_SRC] = 1;

        Sinais[MEM_READ] = 1;

        Sinais[MEM_TO_REG] = 1;

        Sinais[REG_WRITE] = 1;

    }

    else if(opcode == 0xF)
    {
        printf("sw");

        Sinais[ALU_SRC] = 1;

        Sinais[MEM_WRITE] = 1;


    }

    else if(opcode == 0x8)
    {

        printf("beq");

        Sinais[BRANCH] = 1;

    }

    else if(opcode == 0x2)
    {

        printf("jump");

        Sinais[JUMP] = 1;

    }

}


