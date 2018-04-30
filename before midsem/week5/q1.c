/*
A common method is created where initially value of common variable is read. After 4 seconds, the value of the commond variable is updated.
So we create two threads which run the same method simultaneously. If the semaphore had not been used, the newer thread would have read the older value of 
common variable. But with semaphore, we have achieved synchronisation of the critical section
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int common_variable=2;
sem_t mutex;

void* thread (void* arg){
	printf("Entered thread id %d. Now will try to execute the critical section\n\n",(int)pthread_self());

	//critical section
	sem_wait(&mutex); 

	printf("The initial value of the common_variable is %d from thread %d\n\n", common_variable, (int)pthread_self());
	sleep(7);
	common_variable+=4;
	printf("The value the common_variable after writing is %d from thread %d\n\n",common_variable, (int)pthread_self() );

	//exiting
	printf("Exiting the thread %d\n\n", (int)pthread_self());
	sem_post(&mutex);
}

int main(void){
	sem_init(&mutex,0,1);
	pthread_t t1,t2;
	pthread_create(&t1,NULL,thread,NULL);
	pthread_create(&t2,NULL,thread,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	sem_destroy(&mutex);
}