#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){
int pid =fork();
if (pid ==0){
	printf("Inside child\nParents pid is %d", getppid());
	
}
else {
	printf("Inside parent\nChild's pid is %d\n", pid);
}
return 0;
}