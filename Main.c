#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>


    int main() {
        const char *device_path = "/dev/driver_dos_amigos"; // Substitua pelo caminho do seu dispositivo
        int fd = open_device(device_path); // Abre o dispositivo
        char informacao[512]; // Buffer para armazenar informações
        uint32_t dataA = 0;
        uint32_t dataB = 0;

        int x = 70;
        int y = 50;
        set_background(fd, &dataA,&dataB, 3, 5, 6);
        //editar_bloco_background(fd, &dataA,&dataB, 0, 400, 3, 5, 6);
        /*for(int i = 0; i < 80; i++){
            for(int j = 0; j < 60; j++){
                editar_bloco_background(fd, &dataA,&dataB, i, j, 3, 5, 6);
            }
        }*/ // fundo da cor do fundo
        for(int i = 0; i < 80; i++){
            for(int j = 50; j < 60; j++){
                editar_bloco_background(fd, &dataA,&dataB, i, j, 0, 4, 0);
            }
        }
        print_quadrado(fd, &dataA,&dataB, 10, 511, 100, 5, 5, 5, 0);
        print_triangulo(fd, &dataA,&dataB, 2, 320, 280, 15, 3, 4, 2);
        print_triangulo(fd, &dataA,&dataB, 4, 380, 280, 15, 3, 4, 2);
        print_triangulo(fd, &dataA,&dataB, 5, 440, 280, 15, 3, 4, 2);
        print_triangulo(fd, &dataA,&dataB, 6, 500, 280, 15, 3, 4, 2);
        for(int i = 62; i < 65; i++){
            for(int j = 45; j < 50; j++){
                editar_bloco_background(fd, &dataA,&dataB, i, j, 4, 2, 1);
            }
        }
        for(int i = 54; i < 57; i++){
            for(int j = 45; j < 50; j++){
                editar_bloco_background(fd, &dataA,&dataB, i, j, 4, 2, 1);
            }
        }
        for(int i = 46; i < 49; i++){
            for(int j = 45; j < 50; j++){
                editar_bloco_background(fd, &dataA,&dataB, i, j, 4, 2, 1);
            }
        }
        for(int i = 38; i < 41; i++){
            for(int j = 45; j < 50; j++){
                editar_bloco_background(fd, &dataA,&dataB, i, j, 4, 2, 1);
            }
        }   

        //flores abaixo

        print_sprite(fd, &dataA,&dataB, 1, 1, 400,4,3);
        print_sprite(fd, &dataA, &dataB, 1,90, 450,4,4);    
        print_sprite(fd, &dataA,&dataB, 1, 150, 410,4,5);
        print_sprite(fd, &dataA,&dataB, 1, 130, 410,23,11);
        print_sprite(fd, &dataA,&dataB, 1, 200, 400,4,6);
        print_sprite(fd, &dataA,&dataB, 1, 250, 420,4,7);
        print_sprite(fd, &dataA,&dataB, 1, 300, 420,4,8); 
        print_sprite(fd, &dataA,&dataB, 1, 350, 420,4,9); 
        print_sprite(fd, &dataA,&dataB, 1, 355, 450,4,10); 
        print_sprite(fd, &dataA,&dataB, 1, 430, 439, 4,12); 
        print_sprite(fd, &dataA,&dataB, 1, 500, 439, 4,13);


        //pedras abaixo

        print_sprite(fd, &dataA,&dataB, 1, 400, 450,23,11); 
        print_sprite(fd, &dataA,&dataB, 1, 79, 400,23,15);  
        print_sprite(fd, &dataA,&dataB, 1, 79, 400,23,15);  
        print_sprite(fd, &dataA,&dataB, 1, 200, 450,23,17);


        //aviao1
        print_sprite(fd, &dataA,&dataB, 1, 100, 150,6,19); 
        //aviao2
        print_sprite(fd, &dataA,&dataB, 1, 270, 150,6,20); 
        //laser 1
        print_sprite(fd, &dataA,&dataB, 1, 130, 150,13,21);
        //laser 2
        print_sprite(fd, &dataA,&dataB, 1, 200, 150,13,22); 

        //nuvem 1
        print_quadrado(fd, &dataA,&dataB, 8, 100, 100, 2, 7, 7, 7);
        print_quadrado(fd, &dataA,&dataB, 9, 80, 100, 1, 7, 7, 7);
        print_quadrado(fd, &dataA,&dataB, 11, 120, 105, 1, 7, 7, 7);


        //nuvem 2
        print_quadrado(fd, &dataA,&dataB, 12, 200, 70, 2, 7, 7, 7);
        print_quadrado(fd, &dataA,&dataB, 13, 180, 70, 1, 7, 7, 7);
        print_quadrado(fd, &dataA,&dataB, 14, 220, 70, 1, 7, 7, 7);

        //nuvem 3
        print_quadrado(fd, &dataA,&dataB, 16, 335, 98, 1, 7, 7, 7);
        print_quadrado(fd, &dataA,&dataB, 17, 350, 102, 1, 7, 7, 7);
    
        

        
        
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



