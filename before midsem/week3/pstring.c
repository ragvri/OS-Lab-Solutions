#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv){
	char command[30]= "xterm -hold -e ";
	system("gcc dstring.c");
	strcat(command, "./a.out ");
	strcat(command, argv[1]);	
	system(command);	
	
	
	system(command);
}