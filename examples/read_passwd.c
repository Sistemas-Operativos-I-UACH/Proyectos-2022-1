#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h> 

int main(void) {
	char buf[256];
    printf("Leyendo /etc/passwd\n");
    int fd = open("/etc/passwd", O_RDONLY);
    printf("File Descriptor No. = %d/n", fd);
    if (fd == -1) { 
        // print which type of error have in a code 
        printf("Error opening file");
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
