#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Head.h"

#ifdef _WIN32
    #include <windows.h>
    #include <commdlg.h>
#endif

void selecionar_arquivo(char *caminho)
{
#ifdef _WIN32

    OPENFILENAME ofn;
    memset(&ofn, 0, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = caminho;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "Arquivos MEM\0*.mem\0Todos\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn))
    {
        printf("Arquivo selecionado: %s\n", caminho);
    }

#else

    printf("Digite o caminho do arquivo (.mem): ");
    scanf("%s", caminho);

    strcat(caminho, ".mem");

#endif
}

void selecionar_arquivo2(char *caminho)
{
#ifdef _WIN32

    OPENFILENAME ofn;
    memset(&ofn, 0, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = caminho;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 260;
    ofn.lpstrFilter = "Arquivos DAT\0*.dat\0Todos\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn))
    {
        printf("Arquivo selecionado: %s\n", caminho);
    }

#else

    printf("Digite o caminho do arquivo (.dat): ");
    scanf("%s", caminho);

    strcat(caminho, ".dat");

#endif
}

/*
#include <windows.h>
#include <commdlg.h>

void selecionar_arquivo(char *caminho)
{
    //struct do proprio windows para guardar o caminho
    OPENFILENAME ofn;

    //garante que o caminho esta limbo/ tira o lixo de memoria
    ZeroMemory(&ofn, sizeof(ofn));

    // informa o tamanho da struct do windows
    ofn.lStructSize = sizeof(ofn);

    //
    ofn.lpstrFile = caminho;

    //
    ofn.lpstrFile[0] = '\0';

    //
    ofn.nMaxFile = 100;

    //filtro de tipo de arquivos no caso .mem
    ofn.lpstrFilter = "Arquivos MEM\0*.mem\0Todos\0*.*\0";

    //usa o primeiro index
    ofn.nFilterIndex = 1;

    //
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


    //
    if (GetOpenFileName(&ofn))
    {
        printf("Arquivo selecionado: %s\n", caminho);
    }

}


// para .dat

void selecionar_arquivo2(char *caminho)
{
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = caminho;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 260;
    ofn.lpstrFilter = "Arquivos DAT\0*.dat\0Todos\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn))
    {
        printf("Arquivo selecionado: %s\n", caminho);
    }
}

*/

//agora imprime corretamente o valor binario

void print_bin(unsigned short x)
{

    for(int i=15;i>=0;i--)
    {

        printf("%d", (x>>i)&1);

    }

}

// um fix, afinal registradores e memoria de dados não tem 16 bits...

void print_bin8(unsigned char x)
{

    for(int i = 7; i >= 0; i--)
    {

        printf("%d", (x >> i) & 1);

    }

}

//

int main()
{


    // sao simalres entao nao ha necessidade de duas structs de 256 posições
	instro l = {0}, dat = {0};

	//registradores
    signed char reg[8];

    //sinais de controle
    int Sinais[8] = {0};

    int overflow = 0;



    //sinal da ula op
    int ULAop = 0;

    int breaker = 0;

    int dest = 0;

    signed char immx = 0;

    signed char mem = 0;

    unsigned char instruct = 0;

    unsigned short instr = 0;

	int n =0,i=0;

	int tamanho_programa = 0;

	iniat(reg);

	init_mem_incremental(&dat);

	int op=99;

	// flag zero

	int zero = 0;

	// pilha

	Snapshot pilha[500];

	//stackpointer - ponteiro de pilha

	int sp = -1;

	char caminho[100];

	 do {
        printf("\n 1-carregar memoria de instruções \n 2-carregar memoria de dados \n 3-imprimir memorias (instrucoes e dados) \n 4- imprimir banco de registradores \n 5- imprimir todo o simulador \n 6- salvar .asm \n 7- salvar .dat\n 8- executa programa (run)\n 9- executa uma instrução(step) \n 10 - volta uma instrução(back)\n 0-sair da aplicação  \n sua escolha:");
        scanf("%d", &op);

        switch (op) {

            case 1:

                caminho[0] = '\0';

                selecionar_arquivo(caminho);

                if (carregar(&l, caminho, &i) != 0)
                {

                    printf("\n erro ao carregar memoria de instruções");

                }

                else
                {

                    printf("\n memoria de instruções carregada com sucesso");

                }

                break;



            case 2:

                caminho[0] = '\0';

                selecionar_arquivo2(caminho);


                if (carregar_dados(&dat, caminho) != 0)
                {

                    printf("\n erro ao carregar memoria de dados");

                }

                else
                {

                    printf("\n memoria de dados carregada com sucesso");

                }

                break;

            case 3:

                print_mem(&dat);

                print_mem_inst(&l, 256);


                break;

            case 4:

                print_regs(reg);

                break;

            case 5:

                printf("PC(dec): %d \n ", instruct);

                printf("PC(bin): ", instruct);

                print_bin8(instruct);

                printf("\n ");

                print_mem(&dat);

                print_mem_inst(&l, 256);

                print_regs(reg);

                break;

            case 6:

                print_program(&l, 256);

                save_program_asm(&l, 256, "programa.asm");

                break;

            case 7:

                save_mem_dat(&dat, "dados_saida.dat");

                break;


            case 8:

                printf("\n executando progra...\n");

            instruct = 0;
            n = 1;

            //linha de instruções+1 = i e não i = a linha de instruções
            //while (instruct != 10)

            do
            {



                push(pilha, &sp,reg, Sinais, ULAop,overflow, dest, immx,instruct, n);

                printf("\n instrucao %d :\n", n);
                n++;

                printf("Pc Antes da execução\n");
                printf("PC(bin): ");
                print_bin8(instruct);
                printf("\n");

                printf("\n PC(dec): %d",instruct);

                instr = ler(&l, instruct);

                printf("\n Instrucao(HEX): %04X\n", instr);
                printf("Instrucao(BIN): "); print_bin(instr); printf("\n");

                unsigned char opcode = (instr >> 12) & 0xF;
                unsigned char rs = (instr >> 9) & 0x7;
                unsigned char rt = (instr >> 6) & 0x7;
                unsigned char rd = (instr >> 3) & 0x7;
                unsigned char imm = instr & 0x3F;
                unsigned char funct = instr & 0x7;
                unsigned char addr = instr & 0xFF;

                Estender(imm, &immx);

                Decodifica(opcode,Sinais);

                if(opcode == 0x0)
                {
                    tipo(funct);
                    printf("opcode:%d rs:$R%d rt:$R%d rd:$R%d funct:%d\n", opcode, rs, rt, rd, funct);
                    ULAop = funct;
                }
                else if(opcode == 0x4 || opcode == 0xB || opcode == 0xF || opcode == 0x8)
                {
                    printf(" \n opcode:%d rs:$R%d rt:$R%d imm:%d\n", opcode, rs, rt, immx);
                    Tipo2(opcode,&ULAop);
                }
                else if(opcode == 0x2)
                {
                    printf(" \n opcode:%d addr:%d\n", opcode,addr);
                    ULAop = 0;
                }

                dest = Rdest(Sinais, rd, rt);

                signed char A, B;
                read(reg, rs, rt, &A, &B);

                printf(" \n $R%d=%d | $R%d=%d\n", rs, A, rt, B);

                signed char entradaB = ulamx(Sinais, A, B, immx);

                int result = ula(ULAop, A, entradaB, &overflow,&zero);

                printf("Resultado da operacao na ula: %d\n", result);

                if(Sinais[2] == 1)
                {
                    printf("carregou da memoria da memoria %d \n", result);
                    result = dat.instc[(unsigned char)result];
                    printf("o valor: %d \n", result);
                }

                if(Sinais[3] == 1)
                {
                    Store(&dat, result, reg[rt]);
                    printf("armazenou em MEM[%d] o valor %d\n", result, reg[rt]);
                }

                wrmux(Sinais, result);
                esc(reg, dest, result,Sinais[7]);

                if(Sinais[1] == 1)
                {
                    instruct = jump(addr);
                    printf("fez jump para PC=%d\n", instruct);
                }
                else if(Sinais[4] == 1)
                {
                    if(zero == 1)
                    {
                        instruct=branch(instruct,immx);
                        printf("fez brahnc para PC=%d\n", instruct);
                    }
                    else
                    {
                instruct = busca(instruct);
                    }
                }
                else
                {
                    instruct = busca(instruct);
                }

                printf("Estado dos registradores:\n");

                for(int i=0;i<8;i++)
                {
                    printf("$R%d:%d ", i, reg[i]);
                }

                if (overflow)
                {
                    printf("** OVERFLOW OCORREU **\n");
                }

                printf("\nPc depois da execução\n");
                printf("PC(bin): ");
                print_bin8(instruct);
                printf("\n");

                printf("\n PC(dec): %d",instruct);

                breaker = instruct;


            }while (breaker+1 != 1);

                printf("\n--- FIM DO PROGRAMA ---\n");

            break;

            case 9:


                //tira snapshot/foto do programa
                push(pilha, &sp,reg, Sinais, ULAop,overflow, dest, immx,instruct, n);


                // fetch/busca

                //indica qual instrução estamos

                printf("\n instrucao %d :\n", n);
                n++;

                //imprimi o valor atual do pc atraves da funcao criada para binarios la em cima
                printf("Pc Antes da execução\n");
                printf("PC(bin): ");
                print_bin8(instruct);
                printf("\n");

                //valor decimal
                printf("PC(dec): %d",instruct);

                //le a instrução em base no valor de pc/enderço
                instr = ler(&l, instruct);

                //le o conteudo presente no endereço da instrução

                //hexa é mais facil de ler do que binario mas pode ser modificado se neccessario apenas um printf
                printf("Instrucao(HEX): %04X\n", instr);
                printf("Instrucao(BIN): "); print_bin(instr); printf("\n");

                //decodificação/decode


                // separa todos bits da instrução

                unsigned char opcode = (instr >> 12) & 0xF;

                unsigned char rs = (instr >> 9) & 0x7;

                unsigned char rt = (instr >> 6) & 0x7;

                unsigned char rd = (instr >> 3) & 0x7;

                unsigned char imm = instr & 0x3F;

                unsigned char funct = instr & 0x7;

                unsigned char addr = instr & 0xFF;

                //extende imediato

                Estender(imm, &immx);

                //decodifica o opcode e liga seus devidos sinais

                Decodifica(opcode,Sinais);

                //impressões com base no tipo de instrução

                //tipo r

                if(opcode == 0x0)
                {

                    tipo(funct);

                    printf("opcode:%d rs:$R%d rt:$R%d rd:$R%d funct:%d\n", opcode, rs, rt, rd, funct);

                    ULAop = funct;

                }



                //tipo I

                else if(opcode == 0x4 || opcode == 0xB || opcode == 0xF || opcode == 0x8)
                {

                    printf(" \n opcode:%d rs:$R%d rt:$R%d imm:%d\n", opcode, rs, rt, immx);
                    Tipo2(opcode,&ULAop);
                }

                //tipo J


                else if(opcode == 0x2)
                {

                    printf(" \n opcode:%d addr:%d\n", opcode,addr);

                    ULAop = 0;
                }

                //atualiza registrador de destino com base na instrução


                dest = Rdest(Sinais, rd, rt);

                //le os registradores e armazena o valor contido atualmente para impressao

                signed char A, B;

                read(reg, rs, rt, &A, &B);

                printf(" \n $R%d=%d | $R%d=%d\n", rs, A, rt, B);

                // define com base nos sinais define qual é segunda informação que ira para ula, é imm ou reg?

                signed char entradaB = ulamx(Sinais, A, B, immx);


                // envia os dois valores para ula

                int result = ula(ULAop, A, entradaB, &overflow,&zero);

                printf("Resultado da operacao na ula: %d\n", result);




                if(Sinais[2] == 1)
                {
                    printf("carregou da memoria da memoria %d \n", result);

                    result = dat.instc[(unsigned char)result];

                    printf("o valor: %d \n", result);

                }


                if(Sinais[3] == 1)
                {

                Store(&dat, result, reg[rt]);

                printf("armazenou em MEM[%d] o valor %d\n", result, reg[rt]);

                }


                wrmux(Sinais, result);

                esc(reg, dest, result,Sinais[7]);


                //jump e branch

                 if(Sinais[1] == 1)
                {
                    instruct = jump(addr);

                    printf("fez jump para PC=%d\n", instruct);

                }

                else if(Sinais[4] == 1)
                {
                    if(zero == 1)
                    {

                        instruct=branch(instruct,immx);

                        printf("fez brahnc para PC=%d\n", instruct);

                    }

                    else
                    {

                        instruct = busca(instruct);

                    }

                }



                else
                {

                    instruct = busca(instruct);

                }



                printf("Estado dos registradores:\n");

            for(int i=0;i<8;i++)
            {

                 printf("$R%d:%d ", i, reg[i]);

            }

            printf("\nPc depois da execução\n");
            printf("PC(bin): ");
            print_bin8(instruct);
            printf("\n");
            printf("\n PC(dec): %d",instruct);

            if (overflow)
            {

                printf("** OVERFLOW OCORREU **\n");

            }





            break;

            case 10:

                //usa a pilha para voltar no snap shoot/back do mars

                pop(pilha, &sp,reg, Sinais, &ULAop,&overflow, &dest, &immx,&instruct, &n);

            break;

            case 0:

                printf("\n saindo da aplicação");

            break;

            default:

                printf("\n opção invalida porfavor escolha uma das opções fornecidas pelo menu");

            break;

        }

	 }while(op!=0);
}
