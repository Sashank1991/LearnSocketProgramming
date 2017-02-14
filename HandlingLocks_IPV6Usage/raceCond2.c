#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int     mulFactor;
pthread_mutex_t lock;
pthread_cond_t lockCond;

void *PrintMulTable()
{
    pthread_mutex_lock(&lock);
    while(mulFactor==0)
	pthread_cond_wait(&lockCond,&lock);
		int i;
		for(i=0; i<11;i++){
		printf("%d",i*mulFactor);
		}
		printf("\n");
  pthread_mutex_unlock(&lock);

}

void *FetMulFac()
{
    pthread_mutex_lock(&lock);
	int i;
	printf("please enter multiplication Factor \n");
	int enteredVal;
	scanf("%d", &enteredVal);
	printf("enterd multiplication Factor is %d \n",enteredVal);
	mulFactor=enteredVal;
  pthread_cond_signal(&lockCond);
  pthread_mutex_unlock(&lock);
}


int main (int argc, char *argv[])
{

  pthread_t threads[2];
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    if (pthread_cond_init(&lockCond, NULL) != 0)
    {
        printf("\n conditional variable init failed\n");
        return 1;
    }

  pthread_create(&threads[0], NULL, PrintMulTable, NULL);
  pthread_create(&threads[1], NULL, FetMulFac, NULL);
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  printf ("Multiplication Table Printed \n");
  pthread_exit(NULL);
  return 0;

}
