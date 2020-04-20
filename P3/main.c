#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAXLON 1000


void *cuenta(void *);

int main(int argc, char *argv[]){
    pthread_t h1;
    if (argc == 2)
    {
        pthread_create(&h1, NULL, &cuenta, (void *)argv[1]);
        pthread_join(h1, NULL);        
    }else{
        printf("Ingrea un solo parametro.\n");
        exit(0);
    }
    return 0;

}

void *cuenta(void *nombre)
{
    char *name = (char *)nombre;
    int pos, cont= 0, leidos;
    char cadena[MAXLON];
    int fd;
    fd= open(name,O_RDONLY);
   
    while ((leidos =read(fd,cadena,MAXLON))!= 0) {
        
        for (pos= 0; pos< leidos; pos++) {
        if ((cadena[pos]== 'a') || (cadena[pos]== 'A')) {
            cont++;
        }
        }
    }
    printf("Fichero %s: %d caracteres 'a' o 'A' encontrados\n", nombre, cont);
    close(fd);
    pthread_exit(NULL);
}