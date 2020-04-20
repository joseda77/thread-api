#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAXLON 1000

void *cuenta(void *);

int main(int argc, char *argv[])
{
    pthread_t h[argc-1];
    if (argc >= 2)
    {
        for (int i = 0; i < argc - 1; i++)
        {
            pthread_create(&h[i], NULL, &cuenta, (void *)argv[i + 1]);
        }

        for (int i = 0; i < argc - 1; i++)
        {
            pthread_join(h[i], NULL);
            printf("Finish thread number %d \n", i + 1);
        }
    }
    else
    {
        printf("Ingrea uno o varios parametros.\n");
        exit(0);
    }
    return 0;
}

void *cuenta(void *nombre)
{
    char *name = (char *)nombre;
    int pos, cont = 0, leidos;
    char cadena[MAXLON];
    int fd;
    fd = open(name, O_RDONLY);

    while ((leidos = read(fd, cadena, MAXLON)) != 0)
    {

        for (pos = 0; pos < leidos; pos++)
        {
            if ((cadena[pos] == 'a') || (cadena[pos] == 'A'))
            {
                cont++;
            }
        }
    }
    printf("Fichero %s: %d caracteres 'a' o 'A' encontrados\n", nombre, cont);
    close(fd);
    pthread_exit(NULL);
}