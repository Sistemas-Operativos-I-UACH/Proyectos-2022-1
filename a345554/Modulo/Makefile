obj-m += mopet_module.o

all:
	echo "Compilando modulo de ejemplo"
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
