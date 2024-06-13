#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>

int open_device(const char *device_path);
int write_device(int fd, const char *data);
int read_device(int fd, char *buffer, size_t size);
void close_device(int fd);

int verificar_cor(int vermelho, int verde, int azul);
int verificar_cordenadas(int x, int y);
int verificar_cordenadas_poligono(int x, int y);
int verificar_tamanho(int tamanho);
int verificar_sprite(int sprite);
int verificar_registrador(int registrador);
int verificar_bloco(int bloco);
int verificar_endereco(int endereco);

int editar_sprite(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int endereco, int vermelho, int verde, int azul);
int editar_bloco_background(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int x, int y, int vermelho, int verde, int azul);
int print_quadrado(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int endereco, int x, int y, int tamanho, int vermelho, int verde, int azul);
int print_triangulo(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int endereco, int x, int y, int tamanho, int vermelho, int verde, int azul);
int print_sprite(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, uint32_t ativar_sprite, int x, int y, int sprite, int registrador);
int set_background(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int vermelho, int verde, int azul);

#endif /* BIBLIOTECA_H */
