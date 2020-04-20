#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>

#define MAXLON 1000
int mitadVector = 0;


void getNumber(char *);

int main(int argc, char *argv[])
{
    clock_t tiempo_inicio, tiempo_final;
    tiempo_inicio = clock();
    printf("Indica el nombre de un archivo, los numeros en ester archivo deben estar separados y finalizar con una coma ','\n");
    if (argc == 2)
    {
        getNumber(argv[1]);
    }
    tiempo_final = clock();
    printf("Este el tiempo total secuencialmente %ld \n",(tiempo_final-tiempo_inicio));
    return 0;
}

void getNumber(char *nombre)
{
    int i, sum = 0, leidos, cont = 0, units = 0;
    char cadena[MAXLON];
    int fd, data;
    fd = open(nombre, O_RDONLY);
    while ((leidos = read(fd, cadena, MAXLON)) != 0)
    {
        char number[leidos];
        for (i = 0; i < leidos; i++)
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
    
    printf("La suma de los números del fichero es: %d \n", sum);
    close(fd);
}