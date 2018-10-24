#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define N 5
#define HUNGRY 1
#define THINKING 0
#define EATING 2
#define LEFT (id + 4) % N
#define RIGHT (id+1) % N
sem_t mutex;
sem_t s[5];
int phil[5]={0,1,2,3,4};
int state[N];

void test(int id)
{
	if(state[id]==HUNGRY && state[LEFT]!=EATING && state[RIGHT]!=EATING)
	{
		state[id]=EATING;
		printf("\nPhilosopher %d takes %d & %d fork\nPhilosopher %d is eating",id+1,LEFT+1,id+1,id+1);
		sem_post(&s[id]);
	}
}
void take_fork(int id)
{
	sem_wait(&mutex);
	state[id]=HUNGRY;
	printf("\nPhilosopher %d Hungry",id);
	test(id);
	sem_post(&mutex);
	sem_wait(&s[id]);

}
void put_fork(int id)
{
	sem_wait(&mutex);
	state[id]=THINKING;
	printf("\nPhilosopher %d putting fork %d and %d down\n",id + 1, LEFT + 1, id + 1); 
    printf("Philosopher %d is thinking\n", id+ 1); 
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);

}
void *philo(void* id1)
{
	while(1)
	{
		int *i = id1;
		take_fork(*i);
		sleep(1);

		put_fork(*i);
		sleep(2);
	}


}

int main()
{
	printf("N:%d\n",N);
	pthread_t t[5];
	sem_init(&mutex,0,1);
	int i=0;
	for(i=0;i<N;i++)
		sem_init(&s[i],0,0);

	for(i=0;i<N;i++)
	{
		pthread_create(&t[i],NULL,philo,&phil[i]);
		printf("\nPhilosopher %d is thinking",i+1);
	}

	for(i=0;i<N;i++)
		pthread_join(t[i],NULL);
	return 0;
}
