#include<stdio.h>
#include<sys/types.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>
pthread_cond_t var_empty, var_full;
pthread_mutex_t cond_lock;

int b;
static int flag = 0;

main()
{
	pthread_t producer_thread;
	pthread_t consumer_thread;
	void *producer();
	void *consumer();
	pthread_cond_init(&var_empty,NULL);
	pthread_cond_init(&var_full,NULL);
	pthread_mutex_init(&cond_lock,NULL);
	pthread_create(&producer_thread,NULL,producer,NULL);
	pthread_create(&consumer_thread,NULL,consumer,NULL);
	pthread_join(consumer_thread,NULL);
}

void add_buffer(int i)
{
	b=i;
}

int get_buffer()
{
	return b;
}

void *producer()
{
	int i;
	printf("Producer\n");
	
	for(i=0;i<10;i++)
	{
	
		pthread_mutex_lock(&cond_lock);
			while(flag==1)			
				pthread_cond_wait(&var_empty,&cond_lock);
				add_buffer(i);
				flag=1;
				printf("sent %d \n",i);
				pthread_cond_signal(&var_full);
				pthread_mutex_unlock(&cond_lock);
		
	
		
	}

	pthread_exit(NULL);
}

void *consumer()
{
	int i,v;
	printf("Consumer\n");

	for(i=0;i<10;i++)
	{
		pthread_mutex_lock(&cond_lock);
		while(flag==0)
			pthread_cond_wait(&var_full,&cond_lock);
			v=get_buffer();
			printf("got %d\n",v);
			flag=0;
			pthread_cond_signal(&var_empty);
			pthread_mutex_unlock(&cond_lock);
	}

	pthread_exit(NULL);
}
