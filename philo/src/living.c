/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:46:02 by oipadeol          #+#    #+#             */
/*   Updated: 2022/05/27 18:56:13 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	takeforks(t_fork *forks, struct timeval start_time)
{
	t_fork	*nextfork;

	nextfork = forks->next;
	if (pthread_mutex_lock((&(forks->fork_lock))) == 0)
	{
		(forks->count)--;
		print_status(forks, TAKE, start_time);
	}
	if (pthread_mutex_lock((&(nextfork->fork_lock))) == 0)
	{
		if (nextfork->count == 1)
		{
			(nextfork->count)--;
			print_status(forks, TAKE, start_time);
			return (0);
		}
		u_sleeper(forks->input->tt_die * 1000, forks->input->p_num);
	}
	return (1);
}

static void	returnforks(t_fork *forks)
{
	t_fork	*nextfork;

	nextfork = forks->next;
	(forks->count)++;
	pthread_mutex_unlock(&(forks->fork_lock));
	(nextfork->count)++;
	pthread_mutex_unlock(&(nextfork->fork_lock));
}

static void	looper(t_fork *phil, struct timeval start)
{
	while (1)
	{
		if (takeforks(phil, start))
			break ;
		print_status(phil, EAT, start);
		gettimeofday(&(phil->start_eat), NULL);
		u_sleeper(phil->input->tt_eat * 1000, phil->input->p_num);
		returnforks(phil);
		if (!(--(phil->run_cycle)))
			break ;
		print_status(phil, SLEEP, start);
		u_sleeper(phil->input->tt_sleep * 1000, phil->input->p_num);
		print_status(phil, THINK, start);
	}
}

void	*living(void *forks)
{
	t_fork			*phil;
	struct timeval	start;

	phil = forks;
	while (1)
	{
		pthread_mutex_lock(&phil->input->wait_mutex);
		if (phil->input->wait_int == 1)
			break ;
		pthread_mutex_unlock(&phil->input->wait_mutex);
		usleep(1);
	}
	start = phil->input->start;
	pthread_mutex_unlock(&phil->input->wait_mutex);
	gettimeofday(&(phil->start_eat), NULL);
	if (phil->id % 2 == 0)
		u_sleeper(phil->input->tt_eat * 1000, phil->input->p_num);
	looper(phil, start);
	return (NULL);
}

void	print_status(t_fork *phil, int action, struct timeval s_time)
{
	pthread_mutex_lock(&(phil->input->print_lock));
	if (action == THINK)
		printf("%ld	%d	is thinking.\n", time_diff(s_time), phil->id);
	else if (action == TAKE)
		printf("%ld	%d	has taken a fork.\n", time_diff(s_time), phil->id);
	else if (action == EAT)
		printf("%ld	%d	is eating.\n", time_diff(s_time), phil->id);
	else if (action == SLEEP)
		printf("%ld	%d	is sleeping.\n", time_diff(s_time), phil->id);
	if (action == DEATH)
		printf("%ld	%d	died.\n", time_diff(s_time), phil->id);
	else
		pthread_mutex_unlock(&(phil->input->print_lock));
}
