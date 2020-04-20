#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#define MAXLON 1000
int mitadVector = 0;
void *nombre;
pthread_mutex_t lock;
int totalSum = 0;

void *getNumber(void *);

int main(int argc, char *argv[])
{
    clock_t tiempo_inicio, tiempo_final;
    tiempo_inicio = clock();
    pthread_t h1, h2;
    printf("Indica el nombre de un archivo, los numeros en este archivo deben estar separados y finalizar con una coma ','\n");
    if (argc == 2)
    {
        nombre = (void *)argv[1];
        pthread_create(&h1, NULL, &getNumber, (void *)(1));
        pthread_create(&h2, NULL, getNumber, (void *)(2));
    }
    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
    printf("La suma total es: %d \n",totalSum);
    tiempo_final = clock();
    printf("Este el tiempo total con 2 hilos %ld \n",(tiempo_final-tiempo_inicio));
    return 0;
}

int middle(char *chain, int size){
    int cont = 0;
    double position[size];
    for (int i = 0; i < size; i++)
        {
            if (chain[i] == ',')
            {
               position[cont] = i;
               cont ++; 
            }
        }
    
    int middles = (cont / 2);
    int middlePosition = position[middles -1];
    return middlePosition;

}

void *getNumber(void *thread)
{
    int thread_id = (int *)(thread);
    int i, sum = 0, leidos, cont = 0, units = 0;
    char cadena[MAXLON];
    int fd, data;
    fd = open(nombre, O_RDONLY);
    while ((leidos = read(fd, cadena, MAXLON)) != 0)
    {
        int mid = middle(cadena, leidos);
        int init = 0;
        if (thread_id == 1){
            leidos = mid+1;
        }else if(thread_id == 2){
            init = mid;
        }
        char number[leidos];
        for (i = init; i < leidos; i++)
        {
            
            if ((int)(cadena[i]) >= 48 && (int)(cadena[i]) <= 57)
            {
                number[units] = cadena[i];
                units ++; 
            }
            else{
                data = 0;
                for (int j = 0; j < units; j++)
                {
                    int number_unit = (int)(number[j] -'0');
                    data = data + (int)(number_unit * pow (10,units-j-1));
                }
                units =0;
                
            }
            if(units == 0){
                sum = sum + data;
            }
            cont++;
        }
    }


    pthread_mutex_lock(&lock);
    totalSum = totalSum + sum;
    pthread_mutex_unlock(&lock);
    close(fd);
}