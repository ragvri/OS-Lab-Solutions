#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(void){
	int pi[2];
	pipe(pi);
	int pid=fork();
	if (pid==0){
		close(pi[1]);
		char str[100];
		read(pi[0],str,13);   
		printf("%s",str);
	}
	else{
		close(pi[0]);
		write(pi[1],"I am the best",13);
		printf("abc");
	}
}