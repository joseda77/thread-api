#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>


void *factorial (void *);

int main (int argc, char *argv[]) {
  pthread_t h[argc-1];  

  srand(time(0)); 
  printf("Este es el número de parametros %d \n", argc );
  if(argc != 1){
    for (int i= 0; i< argc-1; i++){
        pthread_create (&h[i], NULL, factorial,(void *) argv[i+1]);
    }
       
    for (int i= 0; i< argc-1; i++) {
        pthread_join (h[i], NULL);
        printf ("Finish thread number %d \n", i+1);
    }
  }
  return 0;
}

void *factorial (void *n) {
  long long int resultado= 1;
  int num;
  int num_fact = atoi((char *) n);
  for (num= 2; num<= num_fact; num++) {
    resultado= resultado*num;
    printf ("Factorial de %d, resultado parcial %lld\n", num_fact, resultado);
    sleep (random()%3);
  }
  printf ("El resultado es %d \n", resultado);
  pthread_exit(NULL);
}