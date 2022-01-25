/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:00:46 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/25 05:07:14 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_input *input, t_fork *forks, pthread_t *philos)
{
	t_fork	*one_fork;
	t_fork	*temp;

	pthread_mutex_destroy(&(input->print_lock));
	free(input);
	pthread_mutex_destroy(&(forks->fork_lock));
	one_fork = forks->next;
	temp = forks->next;
	free(forks);
	while (temp != forks)
	{
		temp = temp->next;
		pthread_mutex_destroy(&(one_fork->fork_lock));
		free(one_fork);
		one_fork = temp;
	}
	free (philos);
}

void	join_or_detach_threads(pthread_t *philos, int n, void **watch_ret)
{
	int	i;
	int	*ret;

	i = 0;
	ret = (int *)*watch_ret;
	if (*ret == 1)
		while (i++ < n)
			pthread_detach(philos[i]);
	else
		while (i++ <= n)
			pthread_join(philos[i], NULL);
	free(ret);
}

void	*watchdog(void *forks)
{
	t_fork			*phil;
	struct timeval	start;
	long			tt_die;
	int				*ret;

	phil = forks;
	ret = malloc(sizeof(int));
	*ret = 0;
	tt_die = phil->input->tt_die;
	while (phil->input->wait_int == 0)
		usleep(2);
	u_sleeper(phil->input->tt_die, phil->input->p_num);
	while ((time_diff(phil->start_eat) <= tt_die) && phil->run_cycle)
	{
		usleep(phil->input->p_num / 2);
		phil = phil->next;
	}
	if (!(phil->run_cycle))
		return ((void *)ret);
	else
		print_status(phil, DEATH, phil->input->start);
	*ret = 1;
	return (ret);
}

void	*start_routine(t_input *input, t_fork *forks, pthread_t *philos)
{
	int			i;
	void		*watch_ret;
	pthread_t	watcher;

	i = 0;
	if (pthread_create(&watcher, NULL, &watchdog, forks) != 0)
		return (NULL);
	while (i++ < input->p_num)
	{
		if (pthread_create(philos + i, NULL, &living, forks) != 0)
			return (NULL);
		forks = forks->next;
		usleep(20);
	}
	pthread_mutex_lock(&input->wait_mutex);
	gettimeofday(&(input->start), NULL);
	input->wait_int = 1;
	pthread_mutex_unlock(&input->wait_mutex);
	pthread_join(watcher, &watch_ret);
	join_or_detach_threads(philos, input->p_num, &watch_ret);
	return (0);
}

int	main(int argc, char **argv)
{
	t_input		*input;
	t_fork		*first_fork;
	pthread_t	*philos;

	if (check_bad_input(argc, argv))
		return (1);
	input = malloc(sizeof(t_input));
	initialize_input(input, argc, argv);
	first_fork = create_forks(input->p_num, input);
	if (first_fork == NULL)
		return (3);
	philos = malloc(sizeof(pthread_t) * input->p_num);
	if (philos == NULL)
		return (4);
	start_routine(input, first_fork, philos);
	free_all(input, first_fork, philos);
	return (0);
}
