obj-m += example_module.o

all:
	echo "Compilando modulo super duper de ejemplo"
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
