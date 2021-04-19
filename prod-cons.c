#include<stdio.h>
#include<pthread.h>

void *producer(void*);
void *consumer(void*);

#define MAX_BUF 100
int buffer[MAX_BUF];
int count = 0;
int in = -1, out = -1;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_has_space = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_has_data = PTHREAD_COND_INITIALIZER;

int main(void){
 int i;
 pthread_t thread[2];
 pthread_create(&thread[0], NULL, producer,NULL);
 pthread_create(&thread[1],NULL,consumer,NULL);
 for(i = 0; i < 2; i++)
	pthread_join(thread[i],NULL);
 return 0;
}

void *producer (void *v)
{
	
	int i;
	for(i =0; i< 1000; i++){
		pthread_mutex_lock(&mutex);
		if(count == MAX_BUF)
		{	
			pthread_cond_wait(&buffer_has_space,&mutex);
			printf("???????\n");
		}
		printf("증가중\n");
		in = (in+1) % MAX_BUF;
		buffer[in] = i;
		count++;
		pthread_cond_signal(&buffer_has_data);
		pthread_mutex_unlock(&mutex);
	}
}

void *consumer(void *v)
{
	int i, data;
	int number = 0;	
	for(i =0; i < 1000; i++)
	{
		pthread_mutex_lock(&mutex);
		if(count == 0)
			{pthread_cond_wait(&buffer_has_data,&mutex);
			printf("!!!!!!!!!!\n");
			}
		printf("감소중 %d\n",number++);
		out = (out + 1) % MAX_BUF;
		data = buffer[out];
		count--;
		pthread_cond_signal(&buffer_has_space);
		pthread_mutex_unlock(&mutex);
		//printf("hahaha\n");
		//printf("data = %d\n",data);
	}



}
