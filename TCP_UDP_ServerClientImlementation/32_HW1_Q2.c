// this program switches the execution of processes using execv. this process calls program called summation.cc for execution.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]){
	char *arg[]={"./summation","0"};
	int a =execv("./summation",arg);
	printf( "error occured while starting the process summation");
	exit(0);
}

