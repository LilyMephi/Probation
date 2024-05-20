#include <pthread.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	 pthread_t tid; /* идентификатор потока */
	 pthread_attr_t attr; /* отрибуты потока */
	
	/* получаем дефолтные значения атрибутов */
  	pthread_attr_init(&attr);
  	
  	pthread_exit(0);
}
