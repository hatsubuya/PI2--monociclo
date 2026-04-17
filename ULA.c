#include <stdio.h>
#include <stdlib.h>
#include "Head.h"


int ulamx(int Sinais[8], signed char A, signed char B, signed char immx)
{

    return (Sinais[ALU_SRC]==0) ? B : immx;

}

int ula(int ULAop, signed char A, signed char B, int *overflow, int *zero)
{

    int result = 0;

    *overflow = 0;

    *zero = 0;

    switch(ULAop)
    {

        case 0:

            result = A + B;


            break;

        case 2:

            result = A - B;

            break;

        case 4:

            result = A & B;

            break;

        case 5:

            result = A | B;

            break;

        default:

            result = 0;
    }

    if(result > 127 || result < -128)
    {

        *overflow = 1;

    }

    *zero = (result == 0);


    return result;

}

void Estender(unsigned char imm, signed char *immx)
{

    *immx = (signed char)(imm << 3) >> 3;

}


int wrmux(int Sinais[8], int result)
{

    return result;

}

void tipo(int ULAop)
{

    if(ULAop == 0)
    {

        printf("\n e um add \n");

    }

    else if(ULAop == 2)
    {

        printf("\n e um sub \n");

    }

    else if(ULAop == 4)
    {

        printf("\n e um and \n");

    }

    else if(ULAop == 5)
    {

        printf("\n e um or \n");

    }



}

void Tipo2(unsigned char opcode, int *ULAop)
{
    if(opcode == 0x4 || opcode == 0xB||opcode == 0xF)
    {

        // type I
        *ULAop = 0;

    }


    else if(opcode == 0x8)
    {


        // branch
        *ULAop = 2;

    }

}
