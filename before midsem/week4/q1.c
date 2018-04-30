#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread(void * id){
	printf("CSE OS LAB, by Thread ID %d\n",(int) pthread_self());
	pthread_exit(NULL);
}


int main(void){
	pthread_t id;
	int i=0;
	for(i=0;i<3;++i){
		pthread_create(&id, NULL, thread,NULL);
	}
	pthread_exit(NULL);
	return 0;

}