#include<sys/time.h>
#include<stdio.h>
#include<pthread.h>
#include<errno.h>
pthread_mutex_t region_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t reg_mutex2=PTHREAD_MUTEX_INITIALIZER;

int b;
static int flag=0;
int main ()
{
  pthread_t prod,cons;
  void *producer ();
  void *consumer ();
  pthread_mutex_lock(&reg_mutex2);	
  pthread_create (&prod, NULL,producer, NULL);
  pthread_create (&cons, NULL,consumer, NULL);
  pthread_join (cons, NULL);
}

void
add_buffer (int i)
{
  b = i;
}

int
get_buffer ()
{
  return b;
}

void *
producer ()
{
  int i = 0;
  printf ("i am producer \n");
  for(i=0;i<=10;i++)
    {
      pthread_mutex_lock (&region_mutex);
      add_buffer (i);
      printf("sent %d \n",i);
      //flag=1;
      pthread_mutex_unlock (&reg_mutex2);
     // i = i + 1;
    }
  pthread_exit (NULL);
}

void *
consumer ()
{
  int i, r;
  printf ("i am consumer\n");
  for (i = 0; i<=10; i++)
    {
      pthread_mutex_lock (&reg_mutex2);
      r = get_buffer ();
      pthread_mutex_unlock (&region_mutex);
      printf ("got %d ", r);
    }
  pthread_exit (NULL);
}
