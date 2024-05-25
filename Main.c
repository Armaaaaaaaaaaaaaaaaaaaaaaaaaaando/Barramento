#include <stdio.h>            // Inclui a biblioteca padrão de entrada e saída
#include <fcntl.h>            // Inclui definições para controle de arquivos
#include <sys/mman.h>         // Inclui definições para memória mapeada
#include "/home/aluno/TEC499/LabExemples/auxFiles/address_map_arm.h" // Inclui um arquivo de mapeamento de endereços específicos do hardware

#define DATA_B 0x70  // Define o endereço relativo para o registrador DATA_B
#define DATA_A 0x80  // Define o endereço relativo para o registrador DATA_A
#define START 0xc0   // Define o endereço relativo para o registrador START

// Função principal
int main(){
    int cor = 0; // Inicializa a variável cor com 0
    while(1){
        som(cor); // Chama a função 'som' com o valor atual de cor
        cor += 1; // Incrementa a variável cor
        //sleep(1); // (Comentado) Espera por 1 segundo (não está sendo usado)
        break; // Sai do loop após uma iteração
    }
    return 0; // Retorna 0 para indicar que o programa terminou corretamente
}

// Função para imprimir um sprite na tela
void print_sprite(int* DATA_A_ptr, int* DATA_B_ptr, int registrador,  int sp, int sprite, int x, int y){
    *DATA_A_ptr = registrador << 5; // Ajusta o registrador e armazena no endereço apontado por DATA_A_ptr
    sp = sp << 29; // Ajusta o valor de sp (posição de 29 bits à esquerda)
    x = x << 19; // Ajusta o valor de x (posição de 19 bits à esquerda)
    y = y << 9;  // Ajusta o valor de y (posição de 9 bits à esquerda)

    *DATA_B_ptr = sp | x | y | sprite; // Combina todos os valores e armazena no endereço apontado por DATA_B_ptr
}

// Função para imprimir um polígono na tela
void print_poligono(int* DATA_A_ptr, int* DATA_B_ptr, int endereco,int x, int y, int tamanho, int vermelho, int verde, int azul, int forma, int opcode){
    *DATA_A_ptr = endereco << 4 | opcode; // Ajusta o endereço e opcode e armazena no endereço apontado por DATA_A_ptr
    *DATA_B_ptr = (forma << 31) | (azul << 28) | (verde << 25) | (vermelho << 22) | (tamanho << 18) | (y << 9) | x; // Combina todos os valores e armazena no endereço apontado por DATA_B_ptr
}

// Função que executa operações relacionadas ao som
void som(int cor) {
    volatile int *DATA_B_ptr, *DATA_A_ptr, *START_ptr; // Declara ponteiros para registradores mapeados na memória
    int fd = -1; // Descritor de arquivo inicializado para abrir /dev/mem
    void *LW_virtual; // Ponteiro para a base do mapeamento de memória

    // Abre /dev/mem para acesso a memória física
    if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return (-1);
    }

    // Cria um mapeamento de memória
    LW_virtual = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    if (LW_virtual == MAP_FAILED) {
        printf("ERROR: mmap() failed...\n");
        close(fd);
        return (-1);
    }

    // Ajusta os ponteiros para os registradores mapeados
    DATA_A_ptr = (int *)(LW_virtual + DATA_A);
    DATA_B_ptr = (int *)(LW_virtual + DATA_B);
    START_ptr = (int *)(LW_virtual + START);

    // Variáveis auxiliares
    int x = 20;
    int y = 100;

    // Chama a função para imprimir um polígono na tela
    print_poligono(DATA_A_ptr, DATA_B_ptr, 10, 20, 20, 2, 5, 0, 1, 1, 3);

    // Inicia e para o registrador START
    *START_ptr = 1;
    *START_ptr = 0;

    // Desfaz o mapeamento de memória
    if (munmap(LW_virtual, LW_BRIDGE_SPAN) != 0) {
        printf("ERROR: munmap() failed...\n");
        return (-1);
    }

    // Fecha o descritor de arquivo /dev/mem
    close(fd);

    return 0;
}


