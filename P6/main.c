#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/queue.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>


#define MAXLON 1000


float media(float *number, int n)
{
    float sum = 0;
    float media = 0.0;

    for (int i = 0; i < n; i++)
    {
        sum = sum + number[i];
    }

    media = sum / n;
    return media;
}

/*
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
*/

float *arrayToList(char *nums, int *numElements)
{
    char delimiter[] = " ";
    char *ptr = strtok(nums, delimiter);
    int cantidad = 1, index = 0;
    float *numbers = (float *)malloc(0 * sizeof(float));
    while (ptr != NULL)
    {

        numbers = (float *)realloc(numbers, (cantidad) * sizeof(float));
        float number = atof(ptr);
        *(numbers + index) = number;

        ptr = strtok(NULL, delimiter);
        cantidad = cantidad + 1;
        index = index + 1;
        *numElements = *numElements + 1;
    }
    return numbers;
}

char *getDataFromFile(char *name)
{
    FILE *fd;
    fd = fopen(name, "rt");
    char *nums = (char *)malloc(1 * sizeof(char)), caracter;

    if (fd == NULL)
    {
        printf("Error al abrir el archivo\n");
        exit(0);
    }
    caracter = fgetc(fd);
    while (caracter != EOF)
    {

        char str[2] = "\0";
        str[0] = caracter;
        nums = (char *)realloc(nums, (strlen(nums) + strlen(str) + 1) * sizeof(char));
        strcat(nums, str);
        caracter = fgetc(fd);
    }
    fclose(fd);
    return nums;
}

void calculate_standard_deviation(float *numbers, int n, float media)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = sum + pow((numbers[i] - media), 2);
    }

    float factor = 1 / ((float)n - 1);
    float s = sqrt(factor * sum);
    printf("El valor de la desviación estandar es: %f\n", s);
}

void *desviation(void *file)
{
    int elements = 0;
    char *textNums = getDataFromFile((char *)file);
    float *numbers = arrayToList(textNums, &elements);
    float mediaValue = media(numbers, elements);
    calculate_standard_deviation(numbers, elements, mediaValue);
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    printf("Ingrese solo dos parametros: Nombre del archivo (separado por espacios) y numero de hilos\n");
    if (argc == 3)
    {

        int numThreads = atoi((char *)argv[2]);
        pthread_t h[numThreads];

        for (int i = 0; i < numThreads; i++)
        {
            pthread_create(&h[i], NULL, desviation, (void *)argv[1]);
        }

        for (int i = 0; i < numThreads; i++)
        {
            pthread_join(h[i], NULL);
        }
    }else
    {
        printf("Parametros incorrectos \n");
    }
    

    return 0;
}








