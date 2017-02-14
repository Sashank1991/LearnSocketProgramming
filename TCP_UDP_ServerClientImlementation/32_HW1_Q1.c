//this program creates two children processes named child 1 and child 2 and let them execute separately using fork.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int childId1,childId2,childId3;
	childId1 = fork();
	if(childId1==0){
		printf("child process 1 created.\n");
		int i;				
		for(i=0;i<3;i++){
			printf("Hello,This is the child process 1.\n");
		}	
	}
	else if(childId1>0){
		childId2 = fork();
		if(childId2 == 0){
			printf("child process 2 created\n");
			int i;				
			for(i=0;i<3;i++){
				printf("Hello,This is the child process 2.\n");
			}	
		}
		else if(childId2>0){
			childId3=fork();
			if(childId3==0){
				printf("child process 3 created\n");
				int i;				
				for(i=0;i<3;i++){
					printf("Hello,This is the child process 3.\n");
				}	
			}
			else if(childId3>0){
				int i;				
				for(i=0;i<3;i++){
					printf("Hello,This is the original process.\n");
				}
			}
		}
		else{
			printf("Error encountered while creating a child process 2.");
		}
	}
	else{
		printf("Error encountered while creating a child process 1.");
	}
	
	exit(0);
}
