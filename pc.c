#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

int size,p,c;
pthread_mutex_t b_mutex;
sem_t empty,full;

int* buffer;
int bindex;

void binsert(int v)
{
	if(bindex < size)
		buffer[bindex++]=v;
	else
		printf("Buffer full!");	
}

int bremove()
{
	int v;
	if(bindex > 0)
		v=buffer[--bindex];
	else
		printf("Buffer empty!");	
}

void* producer(void *tno)
{
	int thr_no= *(int*)tno;
	int value=rand()%100;		//creating random numbers
	
	sem_wait(&full);
	pthread_mutex_lock(&b_mutex);
	binsert(value);
	pthread_mutex_unlock(&b_mutex);
	sem_post(&empty);
	printf("\nProducer %d inserted %d in buffer\n",thr_no,value);
	pthread_exit(0);
}

void* consumer(void *tno)
{
	int thr_no= *(int*)tno;
	int value;
	
	sem_wait(&empty);
	pthread_mutex_lock(&b_mutex);
	value=bremove();
	pthread_mutex_unlock(&b_mutex);
	sem_post(&full);
	printf("\nConsumer %d removed %d from buffer\n",thr_no,value);
	pthread_exit(0);
}

int main()
{
	int i,j;
	printf("\nEnter size of buffer:");
	scanf("%d",&size);
	printf("\nEnter number of producers and consumers respectively:");
	scanf("%d%d",&p,&c);
	int thread_num[p+c];
	pthread_t thr[p+c];
	buffer=(int*)malloc(size*sizeof(int));
	
	if(p>=c && p<=size)
	{
		for(i=0;i<size;i++)
		buffer[i]=0;
	
		pthread_mutex_init(&b_mutex,NULL);
		sem_init(&full,0,size);
		sem_init(&empty,0,0);
	
		bindex=0;
		for(i=0;i<p;i++)
		{
			thread_num[i]=i;
			pthread_create(&thr[i],NULL,producer,&thread_num[i]);
		}
		for(j=i;j<(p+c);j++)
		{
			thread_num[j]=j;
			pthread_create(&thr[j],NULL,consumer,&thread_num[j]);
		}
	
		for(i=0;i<(p+c);i++)
		{
			pthread_join(thr[i],NULL);
			pthread_mutex_destroy(&b_mutex);
			sem_destroy(&full);
			sem_destroy(&empty);
		}	
	}
	else
	{
		if(p<c)
			printf("\nNumber of producers not equal to consumers!");
		else if(p>size)
			printf("\nNumber of producers greater than size!");
		else if(c>size)
			printf("\nNumber of consumers greater than size!");
	}		
}
