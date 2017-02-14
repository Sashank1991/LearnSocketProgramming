#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int     mulFactor;
sem_t testSem;

void *PrintMulTable()
{
		sem_wait(&testSem);
		int i;
		for(i=0; i<11;i++){
		printf("%d",i*mulFactor);
		}
		printf("\n");


}

void *FetMulFac()
{

	int i;
	printf("please enter multiplication Factor \n");
	int enteredVal;
	scanf("%d", &enteredVal);
	printf("enterd multiplication Factor is %d \n",enteredVal);
	mulFactor=enteredVal;
	sem_post(&testSem);
}


int main (int argc, char *argv[])
{

  pthread_t threads[2];
    if (sem_init(&testSem,0,0) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }



  pthread_create(&threads[0], NULL, PrintMulTable, NULL);
  pthread_create(&threads[1], NULL, FetMulFac, NULL);
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  printf ("Multiplication Table Printed \n");
  sem_destroy(&testSem);
  pthread_exit(NULL);
  return 0;

}
