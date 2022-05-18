obj-m += example_module.c

all:
	echo "Compilando modulo de ejemplo"
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
