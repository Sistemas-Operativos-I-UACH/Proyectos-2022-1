#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h> 
#include <sys/sysinfo.h> 

void open_file(char *pf)
{
    FILE *file;
    int pid;
    char cmdline_file[255];
    long int priority, nice;

    file = fopen(pf, "r");

    if (file == NULL)
    {
        printf("Null");
    }
    else
    {
        while (!feof(file))
        {
            printf ("--------------------------------------------------------------------------------\n");
			sscanf(linea, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld",
            &pid, cmdline, &NA, &NA, &NA, &NA, &NA, &NA, &NA, &NA, &NA, &NA, &NA, &NA, &NA, &NA, &NA, &priority, &nice);

			printf("PID: %d\n", pid);
			printf("cmdline: %s\n", cmdline);
            printf("Priorty: %ld\n", priority);
            printf("Nice: %ld\n", nice);
            printf ("--------------------------------------------------------------------------------\n");
        }
    }
    fclose(file);
}

void processKU(){
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

				char contenido[256];
				int i = 0;

				while (fgets(contenido, sizeof contenido, fdu) != NULL){
					
					if(i == 8){
						printf("Pertenece a --> ");

						if (contenido[5] == '0'){
							printf("Proceso Kernel\n");
                            printf ("--------------------------------------------------------------------------------\n");
						}
						else{
							printf("Proceso Usiario\n");
                            printf ("--------------------------------------------------------------------------------\n");
						}
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
    unsigned long Size = info.totalram/1000;

	printf ("--------------------------------------------------------------------------------\n");
	printf("Memoria Usada: %ld KB\n\n", Size);
    printf ("--------------------------------------------------------------------------------\n");
    
    closedir(folder);
}


int main(int argc, char **argv)
{
    struct dirent *de;
    DIR *dr = opendir("/proc/");

    char fname[255];
    int i = 0;

    if (dr == NULL)
    {
        printf("Error, /proc fallo al abrir.");
        return 1;
    }

    while ((de = readdir(dr)) != NULL)
        if (strchr(de->d_name, '0') || strchr(de->d_name, '1') || strchr(de->d_name, '2') || strchr(de->d_name, '3') ||
            strchr(de->d_name, '4') || strchr(de->d_name, '5') || strchr(de->d_name, '6') ||
            strchr(de->d_name, '7') || strchr(de->d_name, '8') || strchr(de->d_name, '9'))
        {
            strcpy(fname, "/proc/");
            strcat(fname, de->d_name);
            strcat(fname, "/cmdline");
            printf("Abriendo:\t%s\n", fname);
            open_file(fname);
            processKU();
            i++;
        }
    printf("CANTIDAD DE PROCESOS: %d", i);
    closedir(dr);
    return 0;
}
