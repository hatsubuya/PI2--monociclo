#include <stdio.h>
#include <stdlib.h>
#include "Head.h"

unsigned char busca(unsigned char instruct)
{

    return instruct + 1;

}


unsigned char jump(unsigned char instruct)
{

    return instruct;

}

unsigned char branch(unsigned char instruct,unsigned char imm)
{

    return instruct + imm +1;

}

