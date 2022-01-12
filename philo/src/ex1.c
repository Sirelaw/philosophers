#include "../includes/philo.h"

int mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	for (int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex);
	// 	if (lock == 1){
	// 		// wait until lock is 0
	// 	}
	// 	lock = 1;
		mails++;
		// lock = 0;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t	th[4];
	int i;
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 4; i++)
	{
		if (pthread_create(th + i, NULL, &routine, NULL) != 0){
			perror("Failed to create thread");
			return (1);
		}
		printf("Thread %d has started\n", i);
	}
	for (i = 0; i < 4; i++)
	{
		if (pthread_join(th[i], NULL) != 0){
			return (2);
		}
		printf("Thread %d has finished\n", i);
	}
	printf("Done incrementing from threads. Mails = %d\n", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}