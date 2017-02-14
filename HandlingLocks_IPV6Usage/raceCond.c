#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int     mulFactor;

void *PrintMulTable()
{

		int i;
		for(i=0; i<11;i++){
		printf("%d",i*mulFactor);
		}
		printf("\n");

}

void *FetMulFac()
{
	int i;
	for(i=0; i<100000;i++);
	printf("please enter multiplication Factor \n");
	scanf("%d", &mulFactor);
}


int main (int argc, char *argv[])
{

  pthread_t threads[2];
  pthread_create(&threads[0], NULL, PrintMulTable, NULL);
  pthread_create(&threads[1], NULL, FetMulFac, NULL);
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  printf ("Multiplication Table Printed \n");
  pthread_exit(NULL);
  return 0;

}
