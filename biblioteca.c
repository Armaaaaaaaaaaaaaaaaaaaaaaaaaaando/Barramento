#include "biblioteca.h"
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

    ssize_t ret = write(fd, data, strlen(data));

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
    return 1;
}

int verificar_cordenadas(int x, int y){
    if(x > 639 | y > 479 | x < 0 | y < 0){
        perror("Coodernadas fora dos limites");
        return 0;
    }
    return 1;
}

int verificar_cordenadas_poligono(int x, int y){
    if(x > 511 | y > 479 | x < 0 | y < 0){
        perror("Coodernadas fora dos limites");
        return 0;
    }
    return 1;
}


int verificar_tamanho(int tamanho){
    if(tamanho > 15 | tamanho < 0){
        perror("Tamanho fora dos limites");
        return 0;
    }
    return 1;
}

int verificar_sprite(int sprite){
    if(sprite > 31 | sprite < 0){
        perror("Número do sprite fora dos limite");
        return 0; //   
    }
    return 1;
}

int verificar_registrador(int registrador){
    if(registrador > 31 | registrador < 1){
        perror("Registrador fora dos limites");
        return 0; //   
    }
    return 1;
}

int verificar_bloco(int bloco){
    if(bloco > 4799 | bloco < 0){
        perror("Bloco fora dos limites");
        return 0; //   
    }
    return 1;
}

int verificar_endereco(int endereco){
        if(endereco > 12799 | endereco < 0){
        perror("Endereço fora dos limites");
        return 0; //   
    }
    return 1;
}


int editar_sprite(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int endereco, int vermelho, int verde, int azul){
    char informacao[512];
    if(!verificar_cor(vermelho, verde, azul)) return 0;
    if(!verificar_endereco(endereco)) return 0;
    *DATA_A_ptr = (endereco << 4) | 1;
    *DATA_B_ptr = (azul << 6) | (verde << 3) | vermelho;
    snprintf(informacao, 512, "%ud%u", *DATA_A_ptr, *DATA_B_ptr);
    escrever_no_arquivo(fd, DATA_A_ptr, DATA_B_ptr, informacao);
    return 1; // printou
}

int editar_bloco_background(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int x, int y, int vermelho, int verde, int azul){
    char informacao[512];
    int numero_bloco = y * 80 + x;
    if(!verificar_cor(vermelho, verde, azul)) return 0;
    if(!verificar_cordenadas(x, y)) return 0;
    if(!verificar_bloco(numero_bloco)) return 0;
    *DATA_A_ptr = (numero_bloco << 4) | 2;
    *DATA_B_ptr = (azul << 6) | (verde << 3) | vermelho;
    snprintf(informacao, 512, "%ud%u", *DATA_A_ptr, *DATA_B_ptr);
    escrever_no_arquivo(fd, DATA_A_ptr, DATA_B_ptr, informacao);
    return 1; // printou
}

int print_quadrado(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int endereco, int x, int y, int tamanho, int vermelho, int verde, int azul){
    char informacao[512];
    if(!verificar_cor(vermelho, verde, azul)) return 0;
    if(!verificar_cordenadas_poligono(x, y)) return 0;
    if(!verificar_registrador(endereco)) return 0;
    if(!verificar_tamanho(tamanho)) return 0;
    *DATA_A_ptr = endereco << 4 | 0b0011; // Configura o valor de DATA_A
    *DATA_B_ptr = (0 << 31) | (azul << 28) | (verde << 25) | (vermelho << 22) | (tamanho << 18) | (y << 9) | x; // Configura o valor de DATA_B
    snprintf(informacao, 512, "%ud%u", *DATA_A_ptr, *DATA_B_ptr);
    escrever_no_arquivo(fd, DATA_A_ptr, DATA_B_ptr, informacao);
    return 1; // printou
}

int print_triangulo(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int endereco, int x, int y, int tamanho, int vermelho, int verde, int azul){
    char informacao[512];
    if(!verificar_cor(vermelho, verde, azul)) return 0;
    if(!verificar_cordenadas_poligono(x, y)) return 0;
    if(!verificar_registrador(endereco)) return 0;
    if(!verificar_tamanho(tamanho)) return 0;
    *DATA_A_ptr = endereco << 4 | 3; // Configura o valor de DATA_A
    *DATA_B_ptr = (1 << 31) | (azul << 28) | (verde << 25) | (vermelho << 22) | (tamanho << 18) | (y << 9) | x; // Configura o valor de DATA_B
    snprintf(informacao, 512, "%ud%u", *DATA_A_ptr, *DATA_B_ptr);
    escrever_no_arquivo(fd, DATA_A_ptr, DATA_B_ptr, informacao);
    return 1; // printou
}

// Função para configurar e imprimir um sprite
int print_sprite(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, uint32_t ativar_sprite, int x, int y, int sprite, int registrador) {
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

int set_background(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int vermelho, int verde, int azul){
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
    if (write_device(fd, informacao) < 0) {
        close_device(fd); // Fecha o dispositivo se falhar
        return EXIT_FAILURE;
    }

}

