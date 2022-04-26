#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h> // Entradas del Directorio
#include <sys/sysinfo.h> // Devuelve Estadisticas Globales del Sistema

void Bucle(char *comando){

	long int pid, nice, priority;
    char cmdline[1024];
    char NA[255];

	FILE *fd;
	fd = fopen(comando, "r");
	char linea[255];

	//Si devuelve -1 no hay Archivo al Proceso
	if (fd == NULL){
		printf ("%c%c%c No hay Archivo al Proceso %c%c%c",16,16,16,17,17,17);
	}
	else{

		while (fgets(linea,255,fd) != NULL){
			printf ("--------------------------------------------------------------------------------\n");
			sscanf(linea, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld",
            &pid, cmdline, &NA, &NA, &NA, &NA, &NA, &NA, &NA, &NA,
            &NA, &NA, &NA, &NA, &NA, &NA, &NA, &priority, &nice);

			printf("PID --> %d\n", pid);
			printf("cmdline --> %s\n", cmdline);
		}
		fclose(fd);
	}
}

int main(){
    DIR *folder;
    struct dirent *entry;
    char comando[295];
    folder = opendir("/proc/");
    struct sysinfo info;
    sysinfo(&info);
	
    while((entry = readdir(folder)) != NULL){

        if (isdigit (entry->d_name[0]) != 0){
        	strcpy (comando,"/proc/");
        	strcat (comando,entry->d_name);
        	strcat (comando,"/stat");
        	Bucle(comando);
        	
			sprintf(comando, "/proc/%s/status", entry->d_name);
			FILE *fdu = fopen(comando, "r");

			if(fdu != NULL ){

				char linea[256];
				int i = 0;

				while (fgets(linea, sizeof linea, fdu) != NULL){
					
					if(i == 8){
						printf("Pertenece a --> ");

						if (linea[5] == '0'){
							printf("[Kernel]");
						}
						else{
							printf("[Usuario]");
						}
						
						printf("\n");
						break;
					}
					else{
						i++;
					}
				}
				
				fclose(fdu);
			}
        }
    }

	/////////////////////////////////////////////////////
	//MEMORY
    unsigned long Size = info.totalram/1000;

	printf ("--------------------------------------------------------------------------------\n");
	printf("Memoria Usada --> %ld KB\n\n", Size);
    //Imprimir_Espacio_Memoria("", info.totalram);
    
    closedir(folder);

    return 0;
}
