#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>


void *factorial (void *);

int main (int argc, char *argv[]) {
  pthread_t h1;
  pthread_t h2;  
  srand(time(0)); 
  if (argc== 3) {
    pthread_create (&h1, NULL, factorial, (void *) argv[1]);
    pthread_create (&h2, NULL, factorial, (void *) argv[2]);
    //printf ("El factorial de %s es %lld\n", argv[1], factorial (atoi (argv[1])));
  }
  pthread_join (h1, NULL);
  pthread_join (h2, NULL);
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