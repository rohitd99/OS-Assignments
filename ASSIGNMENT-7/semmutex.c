#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t wrt;
pthread_mutex_t mutex;
int shared_data = 0;
int reader_cnt = 0;

void *credit(void *args)
{

	sem_wait(&wrt);
	printf("Writer %d entered\n",(*(int*)args));
    // sleep(1);
	shared_data += 100;
	printf("Writer %d modified shared data to %d\n",(*(int *)args),shared_data);
	printf("Writer %d left\n",(*(int*)args));
	sem_post(&wrt);
	
}
void *debit(void *args)
{
	sem_wait(&wrt);
	printf("Writer %d entered\n",(*(int*)args));
    // sleep(1);
	shared_data -= 100;
	printf("Writer %d modified shared data to %d\n",(*(int *)args),shared_data);
	printf("Writer %d left\n",(*(int*)args));
	sem_post(&wrt);
	
}

void *reader(void *args)
{
	printf("Reader %d entered\n",*(int*)args);
	pthread_mutex_lock(&mutex);
	reader_cnt++;
	printf("%d Readers are present\n",reader_cnt);
	if(reader_cnt == 1)
	{
		sem_wait(&wrt);
		
	}
	pthread_mutex_unlock(&mutex);
    // sleep(1);
	
	printf("Reader %d: read shared data as %d\n",*((int *)args),shared_data);
	
	pthread_mutex_lock(&mutex);
	reader_cnt--;
	printf("Reader %d left\n",*(int*)args);
	if(reader_cnt == 0)
	{
	sem_post(&wrt);
	}
	pthread_mutex_unlock(&mutex);
	
}

int main(int argc,char *argv[])
{

    printf("Enter the value for shared data : ");
    scanf("%d",&shared_data);
	pthread_t readers[10],writers[5];
    char operations[5] = {'c','d','c','d','c'};
	pthread_mutex_init(&mutex,NULL);
	
	sem_init(&wrt,0,10);
	
	for(int i=0;i<5;i++)
	{
        int* a = malloc(sizeof(int));
        *a = i;
        if(operations[i] == 'c')
	        pthread_create(&writers[i],NULL,&credit,a);
        else
            pthread_create(&writers[i],NULL,&debit,a);
	}
	for(int i=0;i<10;i++)
	{
        int* a = malloc(sizeof(int));
        *a = i;
		pthread_create(&readers[i],NULL,&reader,a);
	}
	for(int i=0;i<10;i++)
	{
	    pthread_join(readers[i],NULL);
	}
	
	for(int j=0;j<5;j++)
	{
	    pthread_join(writers[j],NULL);
	}
	pthread_mutex_destroy(&mutex);
	sem_destroy(&wrt);
	return 0;
	
}
