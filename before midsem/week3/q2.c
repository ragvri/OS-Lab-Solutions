#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){
	int pid = fork();
	if (pid==0){
		printf("Inside child. The parent's pid before the parent exits is %d\n",getppid());
		sleep(4);
		printf("The parent's pid now is %d\n",getppid());
	}
	else{
		sleep(1);
		printf("The parent now exits\n");
		exit(0);
	}
	return 0;
}