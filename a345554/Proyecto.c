#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include<string.h>

int read_proc_file(char *filename, char *info, char *output);
void read_stat(char *buf);
int show_process_info(char *filename);
void MemTotal(char *filename);
void proc_kernel(char *filename);
int is_numeric(char *str);

int main(int argc, char *argv[])
{
    DIR *folder;
    struct dirent *entry;
    folder = opendir("/proc");
    if(folder == NULL)
    {
        perror("Unable to read directory\n");
        return(1);
    }
    while(entry = readdir(folder) )
    {
        if(! is_numeric(entry->d_name) ) {
			printf("DIRECTORIO: %s no es numérico\n", entry->d_name);
			continue;
		}
		show_process_info(entry->d_name);
    }
}

int show_process_info(char *filename)
{
    char output[256];
    
        printf("Process ID: %s\n", filename);
	    printf("Process command line: ");
        read_proc_file(filename, "cmdline", output);
        printf("%s\n", output);
	    printf("Process status:\n");
        read_proc_file(filename, "stat", output);
        read_stat(output);
        MemTotal("/proc/meminfo"); 
}


int read_proc_file(char *filename, char *info, char *output) 
{
	char buf[256];
    char proc_file[256];
    sprintf(proc_file, "/proc/%s/%s", filename, info);
    printf("Leyendo %s\n", proc_file);
    int fd = open(proc_file, O_RDONLY);
    if (fd == -1) 
    { 
        // print which type of error have in a code 
        printf("Unable to read directory\n");
		return 1;
    }

	while (read(fd, &buf, 256)) 
    {
		sprintf(output, "%s", buf);
	}

	close(fd);
    return 0;
}


void read_stat(char *buf) 
{
    long int pid, nice, priority, vsize;
    char cmdline[1024];
    char dummy[255];
    sscanf(buf, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %lu %lu %lu %ld",
        &pid, cmdline, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy,
        &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &priority, &nice, &dummy, &dummy, &dummy, &vsize);
    printf("PID \t");
    printf("\n%d\t%s\t%d\t%d\t%ld\n", pid, cmdline, priority, nice, vsize);

}

void MemTotal(char *filename)
{
    FILE *punteroArchivo = fopen(filename, "r");
    char proc[255];
    if (punteroArchivo == NULL)
    {
        printf("Unable to read directory\n");
    }
    else
    {
        fgets(proc,255,punteroArchivo);  
        printf("%s\n",proc);
        fclose(punteroArchivo);
    }
}

void proc_kernel(char *filename)
{
	FILE *fd=fopen(filename,"r");
	char n;
	
	if(fd==NULL)
    {
		printf("Unable to read directory\n");
	}
    else
    {
		if((n=fgetc(fd))==EOF)
        {
			printf("Proceso de Kernel\n");
		}
        else
        {
			printf("Proceso de Usuario\n");
		}
	}
	fclose(fd);
}

int is_numeric(char *str) {
    for(int i = strlen(str) - 1; i >= 0;  i--) {
		if(str[i] > 47 && str[i] < 58)
            continue;
		return 0;
    }
    return 1;
}