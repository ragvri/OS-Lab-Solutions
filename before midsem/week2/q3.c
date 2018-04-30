#include <stdio.h>
#include <unistd.h>

int global =3;

int main(void){
	int pid=fork();
	if(pid==0){
		printf("Inside child. Initial value of global %d\n", global);
		global+=3;
		printf("Value of global after processing:%d\n", global);
	}
	else{
		printf("Inside parent. Initial value of global %d\n", global);
		global+=3;
		printf("Value of global after processing:%d\n", global);
	}
	return 0;
}