#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include "/home/aluno/TEC499/LabExemples/auxFiles/address_map_arm.h"
#include <asm/io.h>

#define DEVICE_NAME "armando"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("armando");
MODULE_DESCRIPTION("testando");

#define DATA_B 0x70
#define DATA_A 0x80
#define START 0xc0
#define WRFULL 0xb0 



static int major_number;
static struct device* ar_deivice = NULL;
static char mensagem[256];

static volatile int *DATA_A_PTR;            
static volatile int *DATA_B_PTR;            
static volatile int *START_PTR;             
static volatile int *wrfull_ptr; 

static ssize_t ret;

static char mensagem_principal[21];

static void *LW_virtual;

static int dev_open(struct inode* inodep, struct file* filep) {
    printk(KERN_INFO "ar_deivice: Device has been opened.\n");
    return 0;
}

static int dev_release(struct inode* inodep, struct file* filep) {
    printk(KERN_INFO "ar_deivice: Device successfully closed.\n");
    return 0;
}

/*
static void som(volatile int *DATA_A_PTR, volatile int *DATA_B_PTR, volatile int *START_ptr) {
    long num;
    num = strtol(mensagem, NULL, 10);
    printk("a mensagem e: %s\n", mensagem);
    printk("O numero da: %ld\n",num);
    *DATA_A_PTR = 0;
    *DATA_B_PTR = num;

    *START_ptr =0;
    *START_ptr =1;
}
*/


static ssize_t dev_read(struct file* filep, char* buffer, size_t len, loff_t* offset) {
    const char* message = mensagem_principal;
    int message_len = strlen(message);
    int bytes_read = message_len - *offset;

    if (bytes_read > len) {
        bytes_read = len;
    }

    if (bytes_read <= 0) {
        return 0;
    }

    if (copy_to_user(buffer, message + *offset, bytes_read)) {
        return -EFAULT;
    }

    *offset += bytes_read;
    return bytes_read;
}

static ssize_t dev_write(struct file* file, const char* buffer_user, size_t buffer_bytes, loff_t* curs) {
    pr_info("%s: escrevendo!\n", DEVICE_NAME);

    /* Enquanto FIFO's estiverem cheias, espera */
    while (*wrfull_ptr) {}
    
    ret = copy_from_user(mensagem_principal, buffer_user, buffer_bytes);        

    /* Caso ret seja diferente de 0, retorna bytes que não foram copiados */
    if (ret) {
        pr_err("%s: falha ao ler a mensagem do usuario \n", DEVICE_NAME);

        return ret;
    }

    /* Inteiros para DATA_A e DATA_B */
    uint32_t data_a = 0, data_b = 0;

    int i = 0;

    for (i = 0; i < 20; ++i) {
        if (i < 10) {
            /* Pega 10 primeiros números da  */
            data_b = data_b * 10 + (mensagem_principal[i] - '0');
        } else {
            /* Pega os outros 10 números do buffer */
            data_a = data_a * 10 + (mensagem_principal[i] - '0');
        }
    }

    /* Envia instruções para as FIFO's */
    *DATA_A_PTR = 0;
    *DATA_B_PTR = data_b;

    /* Envia sinal para escrita na fila */
    *START_PTR = 1;
    *START_PTR = 0;

    pr_info("%s: escrita feita com sucesso!\n", DEVICE_NAME);

    return 0;
}

static struct file_operations fops = {
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};

static int __init ModuleInit(void) {
    printk(KERN_INFO "Modulo está iniciano agora...\n");

    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "ar_deivice failed to register a major number.\n");
        return major_number;
    }
    printk(KERN_INFO "ar_deivice: registered correctly with major number %d.\n", major_number);


     // Mapear a ponte leve para o espaço de endereços virtuais do kernel
    
    LW_virtual = ioremap(LW_BRIDGE_BASE, LW_BRIDGE_SPAN);
    if (!LW_virtual) {
        printk(KERN_ERR "Erro: falha ao mapear a ponte leve\n");
        return -ENOMEM;
    }

    // Obter ponteiros para os registradores na ponte leve
    DATA_A_PTR = (volatile int *)(LW_virtual + DATA_A);
    DATA_B_PTR = (volatile int *)(LW_virtual + DATA_B);
    START_PTR = (volatile int *)(LW_virtual + START);
    wrfull_ptr = (int*) (LW_virtual + WRFULL);

    printk(KERN_INFO "fim do modulo agora...\n");
    return 0;
}

static void __exit ModuleExit(void) {
    unregister_chrdev(major_number, DEVICE_NAME);
    // Desmapear a ponte leve
    iounmap(LW_virtual);

    printk(KERN_INFO "adeus\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);

