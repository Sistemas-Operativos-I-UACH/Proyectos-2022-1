obj-m += kernel_3er_parcial.o

all:
	echo "Compilando modulo super duper de ejemplo"
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
