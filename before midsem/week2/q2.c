#include <stdio.h>
#include <unistd.h>

int factorial(int n){
	if ((n==0)||n==1)
		return 1;
	else 
		return(n*factorial(n-1));
}

int main(void){
	int n;
	printf("Input a number ");
	scanf("%d",&n);
	printf("PID:%d Factorial:%d\n",getpid(),factorial(n));
	pid_t pid = fork();
	if(pid==0)
	printf("PID:%d Factorial:%d\n",getpid(), factorial(n));
	else
	printf("PID:%d Factorial:%d\n", pid, factorial(n));
	return 0;
	

}