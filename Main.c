#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "/home/aluno/TEC499/LabExemples/auxFiles/address_map_arm.h"


#define DATA_B 0x70
#define DATA_A 0x80
#define START 0xc0

int main(){
    int cor = 0;
    while(1){
        som(cor);
        cor += 1;
        //sleep(1);
    }
    return 0;
}


void som(int cor) {
    volatile int *DATA_B_ptr, *DATA_A_ptr, *START_ptr; // Ponteiro de endereço virtual para os LEDs vermelhos
    int fd = -1; // Usado para abrir /dev/mem
    void *LW_virtual; // Endereços físicos para a ponte leve (light-weight bridge)

    // Abrir /dev/mem para dar acesso a endereços físicos
    if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return (-1);
    }

    // Obter um mapeamento de endereços físicos para endereços virtuais
    LW_virtual = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    if (LW_virtual == MAP_FAILED) {
        printf("ERROR: mmap() failed...\n");
        close(fd);
        return (-1);
    }
    DATA_A_ptr = (int *)(LW_virtual + DATA_A);
    DATA_B_ptr = (int *)(LW_virtual + DATA_B);
    START_ptr = (int *)(LW_virtual + START);

    //abaixo adiciona sprite
    *DATA_A_ptr = 0b000000000000000000000000100000;
    *DATA_B_ptr = 0b100000111100000011110000000011;

    //abaixo define cor do background
    //*DATA_A_ptr = 0;
   //*DATA_B_ptr = 100;

    //abaixo define poligono
    //*DATA_A_ptr = 0b000000000000000000000000100011;
    //*DATA_B_ptr = 0b1110101100000101001011000011100110;
    
    
    *START_ptr = 1;
    *START_ptr = 0;


    //


    // Fechar o mapeamento de endereço virtual previamente aberto
    if (munmap(LW_virtual, LW_BRIDGE_SPAN) != 0) {
        printf("ERROR: munmap() failed...\n");
        return (-1);
    }

    // Fechar /dev/mem para dar acesso a endereços físicos
    close(fd);

    return 0;
}
