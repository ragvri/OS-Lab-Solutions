#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){
	int pid=fork();
	if (pid==0){
		printf("Child's pid is %d\n", getpid());
		sleep(2);
		exit(0);
	}
	else{
		system("ps");
		sleep(5);
		printf("\nProcess after child exits\n");
		system("ps");
		wait(NULL);
		printf("\nProcess after reaping off\n");
		system("ps");
	}
}