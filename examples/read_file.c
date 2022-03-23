#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h> 

int read_file(char *filename);

int main(int argc, char *argv[]) {
    printf("Nombre del programa: %s\n", argv[0]);
    if(argc > 1) {
        printf("Archivo a leer: %s\n", argv[1]);
        read_file(argv[1]);
    }
}

int read_file(char *filename) {
	char buf[256];
    printf("Leyendo %s\n", filename);
    int fd = open(filename, O_RDONLY);
    printf("File Descriptor No. = %d\n", fd);
    if (fd == -1) { 
        // print which type of error have in a code 
        printf("Error opening file\n");
		return 1;
    }

	printf("\n------------------ Start Reading File    -------------------------------\n");
	while (read(fd, &buf, 256)) {
		printf("%s", buf);
	}
	printf("\n------------------ Finished Reading File -------------------------------\n");
 

	close(fd);
    return 0;
}
