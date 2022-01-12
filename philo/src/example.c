#include "../includes/philo.h"

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*printer(void *i)
{
	int j;
	int index = *(int *)i;
	int sum = 0;

	for (int j = 0; j < 5; j++){
		sum += primes[index + j];
	}
	free(i);
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t th[10];
	int	i = 0;
	int *a;

	for (i = 0; i < 2; i++)
	{
		a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(th + i, NULL, &printer, a) != 0)
			perror("Failed to create thread");
	}
	for (i = 0; i < 2; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
	}
	return (0);
}