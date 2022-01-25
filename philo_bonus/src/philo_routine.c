/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:46:02 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/25 19:28:14 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	print_status(t_phil *phil, int action, struct timeval s_time)
{
	sem_wait(phil->input->print_sem);
	if (action == THINK)
		printf("%ld %d	is thinking.\n", time_diff(s_time), phil->id);
	else if (action == TAKE)
		printf("%ld %d	has taken a fork.\n", time_diff(s_time), phil->id);
	else if (action == EAT)
		printf("%ld %d	is eating.\n", time_diff(s_time), phil->id);
	else if (action == SLEEP)
		printf("%ld %d	is sleeping.\n", time_diff(s_time), phil->id);
	sem_post(phil->input->print_sem);
}

static void	takeforks(t_phil *phil, struct timeval start_time)
{
	sem_wait(phil->input->fork_sem);
	print_status(phil, TAKE, start_time);
	sem_wait(phil->input->fork_sem);
	print_status(phil, TAKE, start_time);
}

static void	returnforks(t_phil *phil)
{
	sem_post(phil->input->fork_sem);
	sem_post(phil->input->fork_sem);
}

void	*living(void *philo)
{
	t_phil	*phil;

	phil = philo;
	gettimeofday(&phil->start_eat, NULL);
	if ((phil->id != 1) && (phil->id > (phil->input->p_num / 2)))
		u_sleeper(phil->input->tt_sleep * 1000, phil->input->p_num);
	while (1)
	{
		takeforks(phil, phil->start);
		print_status(phil, EAT, phil->start);
		gettimeofday(&phil->start_eat, NULL);
		u_sleeper(phil->input->tt_eat * 1000, phil->input->p_num);
		returnforks(phil);
		if (!(--phil->run_cycle))
			break ;
		print_status(phil, SLEEP, phil->start);
		u_sleeper(phil->input->tt_sleep * 1000, phil->input->p_num);
		print_status(phil, THINK, phil->start);
	}
	return (NULL);
}

void	*philo_routine(t_phil *phil, struct timeval	s_time)
{
	pthread_t	alive;
	int			tt_die;

	tt_die = phil->input->tt_die;
	phil->start = s_time;
	if (pthread_create(&alive, NULL, &living, phil) != 0)
		return (NULL);
	u_sleeper(tt_die, phil->input->p_num);
	while ((time_diff(phil->start_eat) <= tt_die) && phil->run_cycle)
		usleep(phil->input->p_num / 2);
	if (phil->run_cycle)
	{
		sem_wait(phil->input->print_sem);
		printf("%ld %d	died.\n", time_diff(phil->start), phil->id);
	}
	else
		u_sleeper(phil->input->tt_eat * 1000, phil->input->p_num);
	pthread_detach(alive);
	sem_post(phil->input->done_sem);
	exit(EXIT_SUCCESS);
}
