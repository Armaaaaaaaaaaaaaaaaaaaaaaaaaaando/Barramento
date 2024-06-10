#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>


// Função para abrir o dispositivo
int open_device(const char *device_path) {
    // Tenta abrir o dispositivo no modo leitura e escrita
    int fd = open(device_path, O_RDWR);
    if (fd < 0) {
        // Se falhar, exibe uma mensagem de erro
        perror("Failed to open device");
        return -1;
    }
    return fd;
}

// Função para escrever no dispositivo
int write_device(int fd, const char *data) {
    // Tenta escrever os dados no dispositivo
     printf("Coloc123ou\n");

    ssize_t ret = write(fd, data, strlen(data));
     printf("Colocou321\n");

    if (ret < 0) {
        // Se falhar, exibe uma mensagem de erro
        perror("Failed to write to device");
        return -1;
    }
    return ret;
}

// Função para ler do dispositivo
int read_device(int fd, char *buffer, size_t size) {
    // Tenta ler os dados do dispositivo
    ssize_t ret = read(fd, buffer, size - 1);
    if (ret < 0) {
        // Se falhar, exibe uma mensagem de erro
        perror("Failed to read from device");
        return -1;
    }
    buffer[ret] = '\0'; // Adiciona o terminador nulo na string
    return ret;
}

// Função para fechar o dispositivo
void close_device(int fd) {
    // Tenta fechar o dispositivo
    if (close(fd) < 0) {
        // Se falhar, exibe uma mensagem de erro
        perror("Failed to close device");
    }
}

int verificar_cor(int vermelho, int verde, int azul){
    if(vermelho > 7 | verde > 7 | azul > 7 | vermelho < 0 | verde < 0 | azul < 0){
        perror("Valor de cor fora dos limites");
        return 0; //    
    }
}

int verificar_cordenadas(int x, int y){
    if(x > 639 | y > 479 | x < 0 | y < 0){
        perror("Coodernadas fora dos limites");
        return 0;
    }
}

int verificar_tamanho(int tamanho){
    if(tamanho > 15 | tamanho < 0){
        perror("Tamanho fora dos limites");
        return 0;
    }
}

int verificar_sprite(int sprite){
    if(sprite > 31 | sprite < 0){
        perror("Número do sprite fora dos limite");
        return 0; //   
    }
}

int verificar_registrador(int registrador){
    if(registrador > 31 | registrador < 1){
        perror("Registrador fora dos limites");
        return 0; //   
    }
}

int verificar_bloco(int bloco){
    if(bloco > 4799 | bloco < 0){
        perror("Bloco fora dos limites");
        return 0; //   
    }
}


int editar_bloco_background(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int x, int y, int vermelho, int verde, int azul){
    char informacao[512];
    int numero_bloco = y * 80 + x;
    if(!verificar_cor(vermelho, verde, azul)) return 0;
    if(!verificar_cordenadas(x, y)) return 0;
    if(!verificar_bloco(numero_bloco)) return 0;
    *DATA_A_ptr = (numero_bloco << 4) | 0b0010;
    *DATA_B_ptr = (azul << 6) | (verde << 3) | vermelho;
    snprintf(informacao, 512, "%ud%u", *DATA_A_ptr, *DATA_B_ptr);
    escrever_no_arquivo(fd, DATA_A_ptr, DATA_B_ptr, informacao);
    return 1; // printou
}

int print_quadrado(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int endereco, int x, int y, int tamanho, int vermelho, int verde, int azul){
    char informacao[512];
    if(!verificar_cor(vermelho, verde, azul)) return 0;
    if(!verificar_cordenadas(x, y)) return 0;
    if(!verificar_registrador(endereco)) return 0;
    if(!verificar_tamanho(tamanho)) return 0;
    *DATA_A_ptr = endereco << 4 | 3; // Configura o valor de DATA_A
    *DATA_B_ptr = (azul << 28) | (verde << 25) | (vermelho << 22) | (tamanho << 18) | (y << 9) | x; // Configura o valor de DATA_B
    snprintf(informacao, 512, "%ud%u", *DATA_A_ptr, *DATA_B_ptr);
    escrever_no_arquivo(fd, DATA_A_ptr, DATA_B_ptr, informacao);
    return 1; // printou
}

void print_triangulo(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int endereco, int x, int y, int tamanho, int vermelho, int verde, int azul){
    char informacao[512];
    if(!verificar_cor(vermelho, verde, azul)) return 0;
    if(!verificar_cordenadas(x, y)) return 0;
    if(!verificar_registrador(endereco)) return 0;
    if(!verificar_tamanho(tamanho)) return 0;
    *DATA_A_ptr = endereco << 4 | 3; // Configura o valor de DATA_A
    *DATA_B_ptr = (1 << 31) | (azul << 28) | (verde << 25) | (vermelho << 22) | (tamanho << 18) | (y << 9) | x; // Configura o valor de DATA_B
    snprintf(informacao, 512, "%ud%u", *DATA_A_ptr, *DATA_B_ptr);
    escrever_no_arquivo(fd, DATA_A_ptr, DATA_B_ptr, informacao);
    return 1; // printou
}
/*
// Função para configurar e imprimir um polígono
void print_poligono(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int endereco, int x, int y, int tamanho, int vermelho, int verde, int azul, int forma, int opcode) {
    char informacao[512];
    if(!verificar_cor(vermelho, verde, azul)) return 0;
    if(!verificar_cordenadas(x, y)) return 0;
    if(!verificar_registrador(endereco)) return 0;
    if(!verificar_tamanho(tamanho)) return 0;
    *DATA_A_ptr = endereco << 4 | opcode; // Configura o valor de DATA_A
    *DATA_B_ptr = (forma << 31) | (azul << 28) | (verde << 25) | (vermelho << 22) | (tamanho << 18) | (y << 9) | x; // Configura o valor de DATA_B
    snprintf(informacao, 512, "%ud%u", *DATA_A_ptr, *DATA_B_ptr);
    escrever_no_arquivo(fd, DATA_A_ptr, DATA_B_ptr, informacao);
    return 1; // printou
}
*/
// Função para configurar e imprimir um sprite
void print_sprite(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, uint32_t ativar_sprite, int x, int y, int sprite, int registrador) {
    char informacao[512];
    if(!verificar_sprite(sprite)) return 0;
    if(!verificar_cordenadas(x, y)) return 0;
    if(!verificar_registrador(registrador)) return 0;
    *DATA_A_ptr = (registrador << 4); // Configura o valor de DATA_A
    *DATA_B_ptr = (ativar_sprite << 29) | (x << 19) | (y << 9) | sprite; // Configura o valor de DATA_B
    snprintf(informacao, 512, "%ud%u", *DATA_A_ptr, *DATA_B_ptr);
    escrever_no_arquivo(fd, DATA_A_ptr, DATA_B_ptr, informacao);
    return 1; // printou
}

void set_background(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int azul, int verde, int vermelho){
    char informacao[512];
    if(!verificar_cor(vermelho, verde, azul)) return 0;
    *DATA_A_ptr = 0;
    *DATA_B_ptr = (azul << 6) | (verde << 3) | (vermelho);
    snprintf(informacao, 512, "%ud%u", *DATA_A_ptr, *DATA_B_ptr);
    escrever_no_arquivo(fd, DATA_A_ptr, DATA_B_ptr, informacao);
    return 1; // setou
}


void escrever_no_arquivo(int fd, uint32_t* dataA, uint32_t* dataB, char* informacao){
    // Formata a string com os dois inteiros e o separador
    // Salva a string formatada em uma variável
    // Tenta escrever a mensagem no dispositivo
    if (write_device(fd, *informacao) < 0) {
        close_device(fd); // Fecha o dispositivo se falhar
        return EXIT_FAILURE;
    }

}


int main() {
    const char *device_path = "/dev/driver_dos_amigos"; // Substitua pelo caminho do seu dispositivo
    int fd = open_device(device_path); // Abre o dispositivo
    if (fd < 0) {
        return EXIT_FAILURE; // Sai do programa se falhar ao abrir o dispositivo
    }
    
    char informacao[512]; // Buffer para armazenar informações
    printf("Colocou\n");
    uint32_t dataA = 0;
    uint32_t dataB = 0;

    // Chama a função para configurar um sprite
    //print_poligono(fd, &dataA, &dataB, 10, 320, 240, 2, 5, 0, 1, 1, 3);
    //print_sprite(fd, &dataA, &dataB, 1, 300, 200, 0, 2);
    set_background(fd, &dataA,&dataB, 5, 5, 5);
    printf("Colocou\n");
    
    //aviao
    //print_poligono(fd, &dataA, &dataB, 10, 50, 200, 4, 5, 0, 1, 0, 3);
    //print_sprite(&dataA, &dataB, 2, 300, 200, 2, 5);
    /*
    print_poligono(fd, &dataA, &dataB, 40, 150, 200, 4, 5, 0, 1, 0, 3, informacao);
    print_poligono(fd, &dataA, &dataB, 30, 200, 200, 4, 5, 0, 1, 0, 3, informacao);
    print_poligono(fd, &dataA, &dataB, 50, 230, 215, 1, 5, 0, 1, 0, 3, informacao);
    print_poligono(fd, &dataA, &dataB, 60, 35, 165, 1, 5, 0, 1, 0, 3, informacao);
    print_poligono(fd, &dataA, &dataB, 10, 50, 200, 4, 5, 0, 1, 0, 3, informacao);
    print_poligono(fd, &dataA, &dataB, 20, 100, 200, 4, 5, 0, 1, 0, 3, informacao);
    */

    // Buffer para armazenar a leitura do dispositivo
    char buffer[100];
    if (read_device(fd, buffer, sizeof(buffer)) < 0) {
        close_device(fd); // Fecha o dispositivo se falhar
        return EXIT_FAILURE;
    }

    // Fecha o dispositivo
    close_device(fd); 
    return EXIT_SUCCESS;
}
