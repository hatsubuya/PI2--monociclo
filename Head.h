//struct de memoria
typedef struct {

    unsigned short instc[256];

    int n;

} instro;


//sinais
typedef enum
{

    REG_DST,
    JUMP,
    MEM_READ,
    MEM_WRITE,
    BRANCH,
    ALU_SRC,
    MEM_TO_REG,
    REG_WRITE
} SinalControle;


//estado para desfazer
typedef struct {

    signed char reg[8];

    int Sinais[8];

    int ULAop;

    int overflow;

    int dest;

    signed char immx;

    unsigned char instruct;

    int n;

} Snapshot;


//assinaturas das funções

void save_mem_dat(instro *dat, const char *nome_arquivo);

void print_asm(unsigned short instr);

void print_program(instro *l, int tamanho);

void print_mem_inst(instro *l, int tamanho);

void print_mem(instro *dat);

void print_regs(signed char reg[8]);

void print_bin(unsigned short x);

void print_bin8(unsigned char x);

int carregar_dados(instro *dat, const char *nome_arquivo);

int iniat(signed char reg[8]);

int carregar(instro *l, const char *nome_arquivo, int *i);

unsigned char busca(unsigned char instruct);

unsigned short ler(instro *l, unsigned char instruct);

void Decodifica(unsigned char x, int Sinais[8]);

void Estender(unsigned char imm, signed char *immx);

int read(signed char reg[8], signed char A, signed char B, signed char *outA, signed char *outB);

int ulamx(int Sinais[8], signed char A, signed char B, signed char immx);

int ula(int ULAop, signed char A, signed char B, int *overflow, int *zero);

int wrmux(int Sinais[8], int result);

int esc(signed char reg[8], int dest, signed char A, int key);

int Rdest(int Sinais[8], signed char A, signed char B);

int Store(instro *dat, signed char B, signed char mem);

int temp(signed char A, signed char *mem);

void tipo(int ULAop);

void init_mem_incremental(instro *dat);

unsigned char jump(unsigned char instruct);

unsigned char branch(unsigned char instruct,unsigned char imm);

void push(Snapshot *pilha, int *sp,signed char reg[], int Sinais[], int ULAop,int overflow, int dest, signed char immx,unsigned char instruct, int n);

void pop(Snapshot *pilha, int *sp,signed char reg[], int Sinais[], int *ULAop,int *overflow, int *dest, signed char *immx,unsigned char *instruct, int *n);

void save_program_asm(instro *l, int tamanho, const char *nome_arquivo);

void Tipo2(unsigned char opcode, int *ULAop);
