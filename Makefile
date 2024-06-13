obj-m += driver_dos_amigos.o

all:	
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

run: 
	gcc Main.c biblioteca.c -std=c99 -o Main

	./Main

clearAll:
	rm *
