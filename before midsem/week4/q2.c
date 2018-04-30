#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int global=0;

void* thread(void * x){
	static int i=0;
	i++;
	global++;
	int local=0;
	++local;
	printf("Thread id: %d Static variable: %d global variable: %d local variable: %d\n",(int)pthread_self(), i, global,local );
}
int main(void){
	int i=0;
	pthread_t id;
	for(int i=0;i<5;++i){
		pthread_create(&id, NULL, thread, NULL);
	}
	pthread_exit(NULL);
	return 0;

}