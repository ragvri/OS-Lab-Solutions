#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv){
	FILE * file;
	int i=0;
	char word[50];
	char * file_name;
	file_name= argv[1];
	file = fopen(file_name,"r");
	if (file==NULL){
		printf("Cant open the file\n");
	}
	else{
		while(fscanf(file, "%s", word)!=EOF){
			i++;
			if(i%3==0){
				printf("%s\n",word);
			}
		}
		fclose(file);
	}
}