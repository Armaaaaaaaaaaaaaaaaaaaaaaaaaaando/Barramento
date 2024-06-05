#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
//#define /'dev'/'armando'

// Função para abrir o dispositivo
int open_device(const char *device_path) {
    int fd = open(device_path, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return -1;
    }
    return fd;
}


// Função para escrever no dispositivo
int write_device(int fd, const char *data) {
    ssize_t ret = write(fd, data, strlen(data));
    if (ret < 0) {
        perror("Failed to write to device");
        return -1;
    }
    return ret;
}

// Função para ler do dispositivo
int read_device(int fd, char *buffer, size_t size) {
    ssize_t ret = read(fd, buffer, size - 1);
    if (ret < 0) {
        perror("Failed to read from device");
        return -1;
    }
    buffer[ret] = '\0'; // Null-terminate the string
    return ret;
}

// Função para fechar o dispositivo
void close_device(int fd) {
    if (close(fd) < 0) {
        perror("Failed to close device");
    }
}

int main() {
    const char *device_path = "/dev/armando"; // Substitua pelo caminho do seu dispositivo
    int fd = open_device(device_path);
    if (fd < 0) {
        return EXIT_FAILURE;
    }
    char mensaje[256];
   // const char *message = "Hello, Kernel!";
    printf("digite algo para colocar no kernel: \n");
    scanf("%s",mensaje);
    const char *message = mensaje; 
 if (write_device(fd, message) < 0) {
        close_device(fd);
        return EXIT_FAILURE;
    }

    char buffer[100];
    if (read_device(fd, buffer, sizeof(buffer)) < 0) {
        close_device(fd);
        return EXIT_FAILURE;
    }

   // printf("Data read from device: %s\n", buffer);

    close_device(fd);
    return EXIT_SUCCESS;

    
}

