//this process gives the sum of first five natural numbers and input sent from command line
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sum;
int main(int argc, char* argv[]){
	sum=atoi(argv[1]);
	int i;
	for(i=0; i<5;i++){
		printf("The current value of i is %d \n",i);		
		sum+=i;
	}	
	printf( "The value of the sum is %d \n",sum);
	exit(0);
}
