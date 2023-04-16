#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore1,semaphore2;
int shared_data = 0;
int reader_cnt = 0;
void* add(void* args)
{
    printf("Writer %d entered\n",(*(int*)args));
    sem_wait(&semaphore2);
    // sleep(1);
    printf("Writer %d credited and wrote : %d\n",(*(int*)args),shared_data + 1);
    shared_data++;
    printf("Writer %d left\n",(*(int*)args));
    sem_post(&semaphore2);
    free(args);
}
void* subtract(void* args)
{
    printf("Writer %d entered\n",(*(int*)args));
    sem_wait(&semaphore2);
    // sleep(1);
    printf("Writer %d debited and wrote : %d\n",(*(int*)args),shared_data - 1);
    shared_data--;
    printf("Writer %d left\n",(*(int*)args));
    sem_post(&semaphore2);
    free(args);
}
void* read_(void* args)
{  
    printf("Reader %d entered\n",*(int*)args);
    sem_wait(&semaphore1);
    reader_cnt++;
    
    if(reader_cnt == 1)
        sem_wait(&semaphore2);
    sem_post(&semaphore1);
    // sleep(1);
    printf("%d Readers are present\n",reader_cnt);
    printf("Reader %d read : %d\n",*(int*)args,shared_data);
    printf("Reader %d left\n",*(int*)args);
    sem_wait(&semaphore1);
    
    reader_cnt--;
    if(reader_cnt == 0)
        sem_post(&semaphore2);
    sem_post(&semaphore1);
    free(args);
}
int main(int argc,char* argv[])
{
    printf("Enter the value of shared data: ");
    scanf("%d",&shared_data);
    sem_init(&semaphore1,0,1);
    sem_init(&semaphore2,0,1);
    pthread_t writers[5];
    pthread_t readers[10];
    int operations[5] = {'c','c','d','c','d'};
    for (int i = 0; i < 5; i++)
    {
        int* a = malloc(sizeof(int));
        *a = i;
        if(operations[i] == 'c')
            pthread_create(&writers[i],NULL,&add,a);
        else
            pthread_create(&writers[i],NULL,&subtract,a);
    }
    for(int i = 0;i < 10;i++)
    {
        int* a = malloc(sizeof(int));
        *a = i;
        pthread_create(&readers[i],NULL,&read_,a);
    }
   
    for (int i = 0; i < 10; i++)
    {
        pthread_join(readers[i],NULL);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(writers[i],NULL);
    }
    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);
    return 0;
}