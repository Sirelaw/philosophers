/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:00:46 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/12 23:41:50 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	initialize_input(t_input *input, int argc, char **argv)
{
	input->p_num = ft_atoi(argv[1]);
	input->tt_die = ft_atoi(argv[2]);
	input->tt_eat = ft_atoi(argv[3]);
	input->tt_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input->tt_sleep = ft_atoi(argv[5]);
	else
		input->tt_sleep = 0;
}

int	takefork(t_fork *forks)
{
	if (pthread_mutex_trylock((&(forks->fork_lock))) == 0)
	{	
		(forks->state)--;
		pthread_mutex_unlock(&(forks->fork_lock));
		return(1);
	}
	else
		return (0);
	
}

void	returnfork(t_fork *forks)
{
	pthread_mutex_lock(&(forks->fork_lock));
	(forks->state)++;
	pthread_mutex_unlock(&(forks->fork_lock));
}



void	*living(void *forks)
{
	int				i;
	int				j;
	t_fork			*own_fork;
	struct timeval	current_time;

	own_fork = forks;
	if (own_fork->philo_id % 2 == 0)
	{
		printf("Philosopher %d is sleeping\n", own_fork->philo_id);
		usleep(own_fork->tt_sleep);
	}
	own_fork->state = own_fork->state + takefork((t_fork *)own_fork->next);
	gettimeofday(&current_time, NULL);
	printf("%dms: Philosopher %d is alive %d\n", current_time.tv_usec / 1000, own_fork->philo_id, own_fork->state);
	return (NULL);
}

void	*start_routine(t_input *input, t_fork *forks)
{
	int	i;
	int	*temp;
	pthread_t *philos;
	
	philos = malloc(sizeof(pthread_t) * input->p_num);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i++ < input->p_num)
	{
		if (pthread_create(philos + i, NULL, &living, forks) != 0)
			return (NULL);
		forks = forks->next;
	}
	i = 0;
	while (i++ <= input->p_num)
	{
		if (pthread_join(philos[i], NULL) != 0)
			return (NULL);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_input	*input;
	t_fork	*first_fork;

	if (check_bad_input(argc, argv))
		return (1);
	input = malloc(sizeof(t_input));
	initialize_input(input, argc, argv);
	if (input->p_num == 1)
	{
		first_fork = fork_lstnew(1, 1, input);
		if (first_fork == NULL)
			return (2);
		first_fork->next = fork_lstnew(0, 2, input);
		if (first_fork->next == NULL)
			return (2);
	}
	else
		first_fork = create_forks(input->p_num, input);
	if (first_fork == NULL)
		return (3);
	if (start_routine(input, first_fork) == NULL)
		return (4);
	return (0);
}
