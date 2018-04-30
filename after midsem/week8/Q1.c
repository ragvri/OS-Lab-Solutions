#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static int bss; // variable in bss as unitialised static

int main(void){
	int x=0; // local variable, hence in stack
	printf("The address of stack variable is %p\n\n", (void*)&x);
	int * array = (int *)malloc(5*sizeof(int)); // using malloc, hence in heap
	printf("The address of the top of heap is %p\n\n", sbrk(0)); // sbrk used to increase size of data. If 0 put in its arguments, it returns the address of the top of heap
	printf("The address of a heap variable created using malloc is %p\n\n", (void*)array);
	printf("The address of bss varialbe (static uninitialised variable)  is %p\n\n", (void*)&bss);
	printf("The address of text variable i.e. main() function is %p\n\n", main);

	return 0;


}