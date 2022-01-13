/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:00:46 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/13 23:52:50 by oipadeol         ###   ########.fr       */
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
		input->no_cycle = ft_atoi(argv[5]);
	else
		input->no_cycle = 0;
}

int	takefork(t_fork *forks)
{
	if (pthread_mutex_lock((&(forks->fork_lock))) == 0)
	{
		(forks->state)--;
		return(1);
	}
	else
		return (0);
	
}

int	returnfork(t_fork *forks)
{
	(forks->state)++;
	pthread_mutex_unlock(&(forks->fork_lock));
	return(0);
}

long int	time_diff(struct timeval start_time)
{
	struct timeval	current_time;
	long int		timediff;

	gettimeofday(&current_time, NULL);
	timediff = ((current_time.tv_sec - start_time.tv_sec) * 1000) 
		+ ((current_time.tv_usec - start_time.tv_usec) / 1000);
	return (timediff);
}

void	*living(void *forks)
{
	t_fork			*own_fork;
	struct timeval	start_time;
	int				tot;

	usleep(100);
	gettimeofday(&start_time, NULL);
	own_fork = forks;
	if (own_fork->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&(own_fork->print_lock));
		printf("%ldms: %d	is sleeping\n", time_diff(start_time), own_fork->philo_id);
		pthread_mutex_unlock(&(own_fork->print_lock));
		usleep(own_fork->tt_sleep * 1000);
	}
	while (1)
	{
		tot = takefork(own_fork) + takefork(own_fork->next);
		if ((time_diff(start_time) - own_fork->last_eat) > own_fork->tt_die)
		{
		pthread_mutex_lock(&(own_fork->print_lock));
			printf("%ldms: %d	has passed away\n", time_diff(start_time), own_fork->philo_id);
			return (NULL);
		pthread_mutex_unlock(&(own_fork->print_lock));
		}
		else
		{
			own_fork->last_eat = time_diff(start_time);
		pthread_mutex_lock(&(own_fork->print_lock));
			printf("%ldms: %d	is eating\n", time_diff(start_time), own_fork->philo_id);
		pthread_mutex_unlock(&(own_fork->print_lock));
			usleep(own_fork->tt_eat * 1000);
			tot = returnfork(own_fork) + returnfork(own_fork->next);
		}
		pthread_mutex_lock(&(own_fork->print_lock));
		printf("%ldms: %d	is sleeping\n", time_diff(start_time), own_fork->philo_id);
		pthread_mutex_unlock(&(own_fork->print_lock));
		usleep(own_fork->tt_sleep * 1000);
		pthread_mutex_lock(&(own_fork->print_lock));
		printf("%ldms: %d	is thinking\n", time_diff(start_time), own_fork->philo_id);
		pthread_mutex_unlock(&(own_fork->print_lock));
	}
	
	// own_fork->state = takefork((t_fork *)own_fork->next) + own_fork->state;
	// if ((takefork((t_fork *)own_fork->next) + own_fork->state) == 2)
	// {
	// 	printf("%ldms: %d	has taken a fork\n", time_diff(start_time)00), own_fork->philo_id);
	// 	usleep(own_fork->tt_sleep * 1000);
	// }
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
	t_input		*input;
	t_fork		*first_fork;

	if (check_bad_input(argc, argv))
		return (1);
	input = malloc(sizeof(t_input));
	initialize_input(input, argc, argv);
	pthread_mutex_init(&(input->print_mutex), NULL);
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
