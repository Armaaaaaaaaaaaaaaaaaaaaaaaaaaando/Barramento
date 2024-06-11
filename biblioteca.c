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
        printf("%d\n", numero_bloco);
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

        int x = 70;
        int y = 50;
        set_background(fd, &dataA,&dataB, 3, 5, 6);
        //editar_bloco_background(fd, &dataA,&dataB, 0, 400, 3, 5, 6);
        /*for(int i = 0; i < 80; i++){
            for(int j = 0; j < 60; j++){
                editar_bloco_background(fd, &dataA,&dataB, i, j, 3, 5, 6);
            }
        }*/
        for(int i = 0; i < 80; i++){
            for(int j = 50; j < 60; j++){
                editar_bloco_background(fd, &dataA,&dataB, i, j, 0, 4, 0);
                printf("i: %d, j: %d\n", i, j);
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

