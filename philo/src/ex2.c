#include "../includes/philo.h"

int mails = 0;
pthread_mutex_t	mutex;

void	*roll_dice()
{
	int	value = (rand() % 6) + 1;
	int *ptr = malloc(sizeof(int));

	*ptr = value;
	printf("%d\n", value);
	return ((void *) ptr);
}

int main(int argc, char **argv)
{
	int	*res;
	pthread_t th;

	srand(time(NULL));
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0){
		perror("Failed to create thread");
		return (1);
	}
	printf("Thread has started\n");
	if (pthread_join(th, (void **) &res) != 0){
		return (2);
	}
	printf("Thread has finished\n");
	printf("%d\n", *res);
	free(res);
	return (0);
}