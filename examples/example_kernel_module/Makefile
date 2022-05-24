obj-m += super_duper.o

all:
	echo "Compilando modulo super duper"
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
