#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h>
#include <dirent.h>
#include <string.h>

int read_proc_file(char *filename, char *info, char *output);
void read_stat(char *buf);
int show_process_info(char *filename);
int is_numeric(char *str);

int main(int argc, char *argv[]) {
    DIR *folder;
    struct dirent *entry;
    folder = opendir("/proc");
    if(folder == NULL) {
        perror("Unable to read directory");
        return(1);
    }
	while( entry = readdir(folder) ){
		if(! is_numeric(entry->d_name) ) {
			printf("DIRECTORIO: %s no es numérico\n", entry->d_name);
			continue;
		}
		show_process_info(entry->d_name);
	}
}

int show_process_info(char *filename) {
    char output[256];
	printf("\n---------------------------------------------------\n");
    printf("Process ID: %s\n", filename);
	printf("Process command line: ");
    read_proc_file(filename, "cmdline", output);
    printf("%s\n", output);
	printf("Process status:\n");
    read_proc_file(filename, "stat", output);
	printf("\n---------------------------------------------------\n");
    read_stat(output);
}


int read_proc_file(char *pid, char *info, char *output) {
	char buf[256];
    char proc_file[256];
    sprintf(proc_file, "/proc/%s/%s", pid, info);
    printf("Leyendo %s\n", proc_file);
    int fd = open(proc_file, O_RDONLY);
    if (fd == -1) { 
        // print which type of error have in a code 
        printf("Error opening file\n");
		return 1;
    }

	while (read(fd, &buf, 256)) {
		sprintf(output, "%s", buf);
	}

	close(fd);
    return 0;
}

void read_stat(char *buf) {
    long int pid, nice, priority;
    char cmdline[1024];
    char dummy[255];
    sscanf(buf, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld",
        &pid, cmdline, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy,
        &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &priority, &nice);
    printf("%d\t%s\n", pid, cmdline);
}

int is_numeric(char *str) {
    for(int i = strlen(str) - 1; i >= 0;  i--) {
		if(str[i] > 47 && str[i] < 58)
            continue;
		return 0;
    }
    return 1;
}
