#include <stdio.h>
#include <stdlib.h>
#include "Head.h"

void print_mem_inst(instro *l, int tamanho)
{

    printf("\n--- memoria de Instrucoes ---\n");

    for (int j = 0; j < tamanho; j++)
    {

        printf("Pos %d: ", j);

        print_bin(l->instc[j]);

        printf("\n");

    }

    printf("------------------------\n");

}

int carregar(instro *l, const char *nome_arquivo,int *i)
{
    FILE *arquivo = fopen(nome_arquivo, "r");

    if (!arquivo)
    {

        return -1;

    }


    //são 16 mas tem 2 carateres invisiveis
    char buffer[18];

    *i = 0;

    while (*i < 256 && fgets(buffer, sizeof(buffer), arquivo))
    {

        l->instc[*i] = (unsigned short) strtol(buffer, NULL, 2);

        (*i)++;

    }

    fclose(arquivo);

    return 0;

}

unsigned short ler(instro *l, unsigned char instruct)
{

    return l->instc[instruct];

}
