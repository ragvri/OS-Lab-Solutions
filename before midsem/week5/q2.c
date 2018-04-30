/*
Here a function by the name of thread is created which will be accessed by both the threads. When a thread locks mutex, then the value of lock_number is 
incremented. So if a different thread tries to lock when the value of the variable is one, it means that some other thread has already locked the function.
So we print in that thread that we can't access that function. 
*/

#include <stdio.h>
#include<unistd.h>
#include <pthread.h>
#include <stdlib.h>

pthread_t id[2];
int counter=0;
int lock_number=0;
pthread_mutex_t lock;

void* thread (void* arg){
	counter++; // increasing counter to get thread name
	int temp_counter=counter;

	printf("pthread%d is accessing f()\n\n", temp_counter );
	if (lock_number) // checking if some thread has already locked the variable.
		printf("pthread%d can't access function f() lock acquired by pthread%d\n\n",temp_counter,(temp_counter)%2+1 );

	pthread_mutex_lock(&lock); // acquiring lock
	lock_number++;
	printf("Lock acquired by pthread%d\n \n", temp_counter);
	sleep(4);

	pthread_mutex_unlock(&lock); // releasing lock
	printf("Lock released by ptherad%d\n\n", temp_counter );
	lock_number--; // decrementing lock_number when lock released

}

int main(void){
	pthread_create(&id[0],NULL, &thread, NULL);
	pthread_create(&id[1],NULL, &thread, NULL); // creating 2 threads	
	pthread_join(id[0],NULL);
	pthread_join(id[1],NULL);
	pthread_mutex_destroy(&lock);
	return 0;
}