#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* busy(void* x){
	int * p = (int *)x;
	sleep(2);
	printf("Inside thread with id %d\n", (int)pthread_self());
	pthread_exit(NULL);
}

int main(void){
	pthread_t id;
	pthread_t array[5];
	int i=0;
	for(int i=0;i<5;++i){
		int x=pthread_create(&id, NULL, busy, (void*) id);
		if(x!=0){
			printf("ERROR; return code from pthread_create() is %d\n",x);
			return 0;
		}
		printf("Creating thread %d\n", (int)id);
		array[i]=id;
	}
	for(int i=0;i<5;++i){
		int y= pthread_join(array[i], NULL);
		if(y!=0){
			printf("ERROR; return code from pthread_join() is %d\n",y);
			return 0;
		}
		else{
			printf("Completed join with thread %d having status of %d\n",(int)array[i], y);
		}
	}
	printf("Exiting from the program.\n");
	pthread_exit(NULL);
}