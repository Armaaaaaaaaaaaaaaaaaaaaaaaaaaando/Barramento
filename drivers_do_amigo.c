#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include "/home/aluno/TEC499/LabExemples/auxFiles/address_map_arm.h"
#include <asm/io.h>

#define DEVICE_NAME "driver_dos_amigos"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Armando");
MODULE_DESCRIPTION("Driver");

#define DATA_B 0x70
#define DATA_A 0x80
#define START 0xc0
#define WRFULL 0xb0

static int major_number;
static struct device* ar_deivice = NULL;

static volatile int *DATA_A_PTR;            
static volatile int *DATA_B_PTR;            
static volatile int *START_PTR;             
static volatile int *wrfull_ptr; 

static ssize_t ret;

static char mensagem_principal[65];

static void *LW_virtual;

// Função chamada quando o dispositivo é aberto
static int dev_open(struct inode* inodep, struct file* filep) {
    printk(KERN_INFO "ar_deivice: Device has been opened.\n");
    return 0;
}

// Função chamada quando o dispositivo é fechado
static int dev_release(struct inode* inodep, struct file* filep) {
    printk(KERN_INFO "ar_deivice: Device successfully closed.\n");
    return 0;
}

// Função para separar dois inteiros de uma string
void separarInteiros(const char *str, uint32_t *num1, uint32_t *num2) {
    int i = 0;
    while (str[i] != '\0') {
        if(str[i] == 'd'){
            i++;
            break;
        } 
        *num1 = *num1 * 10 + (str[i] - '0');
        printk("num1: %u\n", *num1);
        i++;
    }
    while (str[i] != '\0') {
        *num2 = *num2 * 10 + (str[i] - '0');
        printk("num2: %u\n", *num2);
        i++;
    }
}

// Função chamada quando o dispositivo é lido
static ssize_t dev_read(struct file* filep, char* buffer, size_t len, loff_t* offset) {
    // Aponta para a mensagem armazenada em mensagem_principal
    const char* message = mensagem_principal;
    // Calcula o comprimento da mensagem
    int message_len = strlen(message);
    // Calcula quantos bytes ainda não foram lidos
    int bytes_read = message_len - *offset;

    // Se o tamanho da mensagem restante for maior que o buffer do usuário, ajusta bytes_read para o tamanho do buffer do usuário
    if (bytes_read > len) {
        bytes_read = len;
    }

    // Se não houver mais bytes para ler, retorna 0 indicando que a leitura está completa
    if (bytes_read <= 0) {
        return 0;
    }

    // Copia os dados da mensagem para o buffer do usuário. Se falhar, retorna um erro
    if (copy_to_user(buffer, message + *offset, bytes_read)) {
        return -EFAULT;
    }

    // Atualiza o offset para refletir a nova posição de leitura
    *offset += bytes_read;
    // Retorna o número de bytes lidos
    return bytes_read;
}


// Função chamada quando o dispositivo é escrito
static ssize_t dev_write(struct file* file, const char* buffer_user, size_t buffer_bytes, loff_t* curs) {
    pr_info("%s: escrevendo!\n", DEVICE_NAME);
    memset(mensagem_principal,0,sizeof(mensagem_principal));
    // Enquanto FIFO estiver cheia, espera
    while (*wrfull_ptr) {}
    ret = copy_from_user(mensagem_principal, buffer_user, buffer_bytes);        
    printk(KERN_INFO "mensagemp %s, buffer user %s\n", mensagem_principal, buffer_user);
    // Caso ret seja diferente de 0, retorna bytes que não foram copiados
    if (ret) {
        pr_err("%s: falha ao ler a mensagem do usuario \n", DEVICE_NAME);
        return ret;
    }

    // Inteiros para DATA_A e DATA_B
    uint32_t data_a = 0, data_b = 0;

    // Separa os inteiros da mensagem principal
    separarInteiros(mensagem_principal, &data_a, &data_b);
    // Envia instruções para as FIFO's
    *DATA_A_PTR = data_a;
    *DATA_B_PTR = data_b;

    // Envia sinal para escrita na fila
    *START_PTR = 1;
    *START_PTR = 0;

    pr_info("%s: escrita feita com sucesso!\n", DEVICE_NAME);

    return 0;
}

// Estrutura que define as operações do dispositivo
static struct file_operations fops = {
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};

// Função chamada na inicialização do módulo
static int __init ModuleInit(void) {
    printk(KERN_INFO "Modulo está iniciano agora...\n");

    // Registra um dispositivo de caractere e obtém um número principal
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "ar_deivice failed to register a major number.\n");
        return major_number;
    }
    printk(KERN_INFO "ar_deivice: registered correctly with major number %d.\n", major_number);
    
    // Mapeia a ponte leve para o espaço de endereços virtuais do kernel
    LW_virtual = ioremap_nocache(LW_BRIDGE_BASE, LW_BRIDGE_SPAN);
    if (!LW_virtual) {
        printk(KERN_ERR "Erro: falha ao mapear a ponte leve\n");
        return -ENOMEM;
    }

    // Obtém ponteiros para os registradores na ponte leve
    DATA_A_PTR = (volatile int *)(LW_virtual + DATA_A);
    DATA_B_PTR = (volatile int *)(LW_virtual + DATA_B);
    START_PTR = (volatile int *)(LW_virtual + START);
    wrfull_ptr = (int*) (LW_virtual + WRFULL);

    printk(KERN_INFO "fim do modulo agora...\n");
    return 0;
}

// Função chamada na remoção do módulo
static void __exit ModuleExit(void) {
    unregister_chrdev(major_number, DEVICE_NAME);
    // Desmapeia a ponte leve
    iounmap(LW_virtual);

    printk(KERN_INFO "adeus\n");
}

// Macros para definir funções de inicialização e saída do módulo
module_init(ModuleInit);
module_exit(ModuleExit);
