#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <sys/sysinfo.h> //returns certain statistics on memory and swap usage, as
                         //well as the load average.

void printmemsize(char *str, unsigned long ramsize) { //sysfunc			]
        printf("%s: %ld KB\n",str, ramsize/1024); //sysfunc				]---- Esto se utiliza para mostrar la memoria
}  //sysfunc															]

int i = 0;

void ciclo(char *arg){

	char state, name[32];
    int pid, ppid, pgrp, session, tty, tpgid, nlwp;
    unsigned long flags, min_flt, cmin_flt, maj_flt, cmaj_flt, vsize;
    unsigned long long utime, stime, cutime, cstime, start_time;
    long priority, nice, alarm, rss;
	FILE *fd; //Se usa fd para hacer las busquedas
	fd = fopen(arg, "r");
	char linea[255];

	if (fd==NULL){
		printf ("ERROR, ESTE PROCESO NO EXISTE"); //EN caso de que el procesa que se busca no exista se muestra este mensaje de error
		}else{
		while (fgets(linea,255,fd)!=NULL){
			printf ("=====================\n");
			printf ("       %d            \n", i);
            printf ("=====================\n");
			sscanf(linea, "%d %s " "%c " "%d %d %d %d %d " "%lu %lu %lu %lu %lu " "%Lu %Lu %Lu %Lu "
			"%ld %ld " "%d " "%ld " "%Lu " "%lu " "%ld", &pid, name, &state, &ppid, &pgrp, &session, &tty, &tpgid,
			&flags, &min_flt, &cmin_flt, &maj_flt, &cmaj_flt, &utime, &stime, &cutime, &cstime, &priority, &nice,
			&nlwp, &alarm, &start_time, &vsize, &rss);
			printf ("PID: %d\n" "nombre: %s\n" "Estado: %c\n" "PPID: %d\n" "Prioridad: %ld\n" "Tamaño: %lu\n" "RAM : %ld KiB\n", //Aqui se imprimen los procesos
			pid, name, state, ppid, nice, vsize, rss);
			i++;
		}
		fclose(fd);
		}
		}

int main(){
    DIR *folder;	
    struct dirent *entry;
    char arg[295];
    folder = opendir("/proc/");       
    struct sysinfo info;
    sysinfo(&info);
	
    while((entry=readdir(folder))!=NULL){
        if (isdigit (entry->d_name[0]) != 0){									//Esto sirve para identificar el tipo											
        	strcpy (arg,"/proc/");												//de proceso que usan los procesos, si es del Kernel o del Usuario
        	strcat (arg,entry->d_name);
        	strcat (arg,"/stat");
        	ciclo(arg);
        	
		sprintf(arg, "/proc/%s/status", entry->d_name);
		FILE *fdu = fopen(arg, "r");

		if ( fdu != NULL )
		{
			char linea[256];
			int contador = 0;
			while (fgets(linea, sizeof linea, fdu) != NULL)
			{
				if (contador == 8 && linea[5] == '0')
				{
					printf("Tipo de proceso: Kernel\n", linea);
					break;
				}else if(contador== 8){
					printf("Tipo de proceso: Usuario\n", linea);
					break;
				}
				else
				{
					contador++;
				}
			}
			fclose(fdu);
		}
        }
    }
	printf("\n\n");
    printf ("=============================\n");
    printmemsize("MEMORIA TOTAL DEL SISTEMA:", info.totalram); //Imprimir la memoria total del sistema
    printf ("=============================\n");
    closedir(folder);
    return 0;
}