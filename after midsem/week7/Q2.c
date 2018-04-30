#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

sem_t question;
sem_t answer;
sem_t student_lock;
int temp;

// Student starts to ask question
void QuesStart(int id){
	printf("Student %d started asking question.\n", id);
	temp = id;
	return;
}

// Student finishes question and makes question semaphore 1. And then waits for teacher to answer the question.
void QuesEnd(int id){
	sem_post(&question);
	sem_wait(&answer);
	printf("Student %d question ends\n", id);
	return;
}

// Teacher waits for the question to end.
void AnsStart(){
	sem_wait(&question);
	printf("Professor started answering question of student %d\n", temp );
	return;

}

// Teacher finishes answering the question. Now releases the answer semaphore for the student.
void AnsEnd(){
	printf("Professor finished answering question of student %d\n", temp);
	sem_post(&answer);
	return;
}

void * Student(void * arg){
	int id = *((int *)arg);
	printf("Student %d enters the class\n", id);
	while(1){
		sem_wait(&student_lock);
		QuesStart(id);
		sleep(0.5);
		QuesEnd(id);
		sem_post(&student_lock);
		sleep(rand()%10);
	}
}

int main(void){
	// initialising the question and answer semaphore with 0 and student_lock semaphore with 1
	sem_init(&question,0,0);
	sem_init(&answer,0,0);
	sem_init(&student_lock,0,1);
	pthread_t x;
	int a;
	printf("Enter the number of students in the class\n");
	scanf("%d", &a);
	int i;
	for(i=1;i<=a;++i){
		pthread_create(&x, NULL, Student, &(i)); // creating student thread.
		sleep(1);
	}

	while(1){
		AnsStart();
		sleep(3);
		AnsEnd();

	}
	return 0;


}