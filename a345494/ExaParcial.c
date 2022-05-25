#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include <ctype.h>

int leer_archivo_procesos(char *filename, char *info, char *output);
int mostrar_procesos_activos(char *filename);
void leer(char *buf);
void diferenciar(char *filename);
void memoria_consumida(char *filename);


int main(int argc, char *argv[]){
    DIR *folder;
    struct dirent *entry;
    folder = opendir("/proc");
    while(entry = readdir(folder) ){
        printf("leyendo archivo: %s",entry->d_name);
        mostrar_procesos_activos(entry->d_name);
    }
    //memoria_consumida("/proc/meminfo");
}


int mostrar_procesos_activos(char *filename){
    
        if (isdigit (filename[0]) == 0){
            return 1;
        }
    	char output[256];
        printf("ID  de proceso: %s\n", filename);
	    printf("Comando del proceso: ");
        leer_archivo_procesos(filename, "cmdline", output);
        printf("%s\n", output);
	    printf("Estado del proceso:\n");
        leer_archivo_procesos(filename, "stat", output);
        leer(output);
}
int leer_archivo_procesos(char *filename, char *info, char *output) {
	char buf[256];char proc_file[256];
    sprintf(proc_file, "/proc/%s/%s", filename, info);
    printf("Leyendo %s\n", proc_file);
    int fd = open(proc_file, O_RDONLY);
	while (read(fd, &buf, 256)) {
		sprintf(output, "%s", buf);
	}
	close(fd);
    return 0;
}
void leer(char *buf) {
    long int pid, nice, priority, vsize;
    char cmdline[1024];
    char dummy[255];
    sscanf(buf, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %lu %lu %lu %ld",
        &pid, cmdline, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy,
        &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &priority, &nice, &dummy, &dummy, &dummy, &vsize);
    printf("%d\t%s\t%d\t%d\t%ld\n", pid, cmdline, priority, nice, vsize);

}
void diferenciar(char *filename){
	FILE *fd=fopen(filename,"r");
	char n;
	if((n=fgetc(fd))==EOF){
		printf("Es un proceso de Kernel\n");
	}
    else{
		printf("Es un proceso de Usuario\n");
	}
	fclose(fd);
}
void memoria_consumida(char *filename){
    FILE *punteroArchivo = fopen(filename, "r");
    char proc[255];
    fgets(proc,255,punteroArchivo);
    printf("%s\n",proc);
    fclose(punteroArchivo);
}
