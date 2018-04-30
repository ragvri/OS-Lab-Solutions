#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

# define no_philos 5
# define no_forks 5

int allocation_matrix[no_philos][no_philos]={0};
int request_matrix[no_philos][no_forks]={0};

sem_t is_available[no_forks];
pthread_mutex_t print_mutex;

void pick(int id, int fork_id){
	request_matrix[id][fork_id]=1;
	sem_wait(&is_available[fork_id]);
	request_matrix[id][fork_id]=0;
	allocation_matrix[id][fork_id]=1;

}

void drop(int philos_id, int fork_id){
	allocation_matrix[philos_id][fork_id]=0;
	sem_post(&is_available[fork_id]);

}

void print(){
	pthread_mutex_lock(&print_mutex);
	printf("Allocation Matrix is:\n");
	for(int i=0;i<no_philos;++i){
		for(int j=0;j<no_philos;++j){
			printf("%d ", allocation_matrix[i][j]);
		}
		printf("\n");
	}

	printf("request_matrix is:\n");
	for(int i=0;i<no_philos;++i){
		for(int j=0;j<no_philos;++j){
			printf("%d ", request_matrix[i][j]);
		}
		printf("\n");
	}
	pthread_mutex_unlock(&print_mutex);	
}

void* philosopher(void* arg){
	int philos_id=*(int*)arg;
	while(1){
		int left_fork=philos_id;
		int right_fork=left_fork+1%no_philos;
		sleep(0.5);
		pick(philos_id,left_fork);
		printf("Philosopher %d grabs fork %d (left)\n",philos_id,left_fork );
		sleep(1);
		pick(philos_id,right_fork);
		if(allocation_matrix[philos_id][left_fork]==0){
			pick(philos_id, left_fork);
			printf("Philosopher %d grabs fork %d (left)\n",philos_id,left_fork );
		}
		printf("Philosopher %d grabs fork %d (right)\n", philos_id, right_fork);
		printf("Philosopher %d starts eating\n", philos_id);
		sleep(1);
		print();
		printf("Philosopher %d ends eating and releases fork %d(left) and %d (right)\n", philos_id, left_fork, right_fork );
		drop(philos_id,left_fork);
		drop(philos_id, right_fork);
		printf("Philosopher %d starts thinking\n",philos_id );

	}
}

int main(void){
	pthread_t threads[no_philos];
	pthread_mutex_init(&print_mutex, NULL);
	for(int i=0;i<no_forks;++i)
		sem_init(&is_available[i], 0,1);

	for(int i=0; i<no_philos;++i){
		int x = pthread_create(&threads[i], NULL, philosopher, &i);
		printf("Philosopher %d starts thinking\n", i);
		sleep(0.001);
	}

	while(1){
		int flag=0;
		for(int i=0;i<no_philos;++i){
			if(allocation_matrix[i][i]==0){
				flag=1;
				break;
			}
		}
		if(flag==1)
			continue;
		else{
			printf("Parent detects deadlock, going to initiate recovery\n");
			int drop_id = rand()%no_philos;
			printf("Parent preempts Philosopher %d\n", drop_id);
			drop(drop_id,drop_id);
			print();
			sleep(1);
		}
	}

}