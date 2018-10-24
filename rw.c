#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define MAX 100
int readCount=0,number=0;
sem_t mutex,writee;
void* reader(void*p)
{
int slptm=rand()%5;
sleep(slptm);
sem_wait(&mutex);
readCount++;
if(readCount==1)
sem_wait(&writee);
sem_post(&mutex);
printf("Reader Read %d\n",number);
sem_wait(&mutex);
readCount--;
if(readCount==0)
sem_post(&writee);
sem_post(&mutex);
}
void* writer(void*p)
{
int slptm=rand()%5;
sleep(slptm);
sem_wait(&writee);
number=rand()%100;
printf("Writer Wrote %d\n",number);
sem_post(&writee);
}
int main()
{
int i,num_wt,num_rt;
pthread_t tid_rt[MAX],tid_wt[MAX];
sem_init(&mutex,0,1);
sem_init(&writee,0,1);
do
{
printf("Enter number of Readers\n");
scanf("%d",&num_rt);
}while(num_rt>MAX);
do
{
printf("Enter the number of Writers\n");
scanf("%d",&num_wt);
}while(num_wt>MAX);
for(i=0;i<num_rt;i++)
pthread_create(&tid_rt[i],NULL,reader,NULL);
for(i=0;i<num_wt;i++)
pthread_create(&tid_wt[i],NULL,writer,NULL);
for(i=0;i<num_wt;i++)
pthread_join(tid_wt[i],NULL);
for(i=0;i<num_rt;i++)
pthread_join(tid_rt[i],NULL);
}
