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

// Função para configurar e imprimir um polígono
void print_poligono(uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int endereco, int x, int y, int tamanho, int vermelho, int verde, int azul, int forma, int opcode) {
    *DATA_A_ptr = endereco << 4 | opcode; // Configura o valor de DATA_A
    *DATA_B_ptr = (forma << 31) | (azul << 28) | (verde << 25) | (vermelho << 22) | (tamanho << 18) | (y << 9) | x; // Configura o valor de DATA_B
}

// Função para configurar e imprimir um sprite
void print_sprite(uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, uint32_t sp, uint32_t x, uint32_t y, uint32_t sprite, uint32_t registrador) {
    *DATA_A_ptr = (registrador << 4) | 0b0000; // Configura o valor de DATA_A
    *DATA_B_ptr = (sp << 29) | (x << 19) | (y << 9) | sprite; // Configura o valor de DATA_B
}

int main() {
    const char *device_path = "/dev/armando"; // Substitua pelo caminho do seu dispositivo
    int fd = open_device(device_path); // Abre o dispositivo
    if (fd < 0) {
        return EXIT_FAILURE; // Sai do programa se falhar ao abrir o dispositivo
    }
    
    char informacao[512]; // Buffer para armazenar informações
    printf("Colocou\n");
    uint32_t dataA = 0;
    uint32_t dataB = 0;

    // Chama a função para configurar um sprite
    // print_poligono(&dataA, &dataB, 10, 50, 50, 2, 5, 0, 1, 1, 3);
    // print_sprite(&dataA, &dataB, 2, 1, 5, 320, 240);
    print_sprite(&dataA, &dataB, 1, 300, 200, 0, 2);

    // Imprime os valores configurados
    printf("dataA: %u, dataB: %u\n", dataA, dataB);

    // Formata a string com os dois inteiros e o separador
    snprintf(informacao, 512, "%ud%u", dataA, dataB);
    printf("%s\n", informacao);

    // Salva a string formatada em uma variável
    const char *mensagem_escreve_arquivo = informacao; 

    // Tenta escrever a mensagem no dispositivo
    if (write_device(fd, mensagem_escreve_arquivo) < 0) {
        close_device(fd); // Fecha o dispositivo se falhar
        return EXIT_FAILURE;
    }

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
