/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:46:02 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/23 00:00:21 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	takeforks(t_phil *phil, struct timeval start_time)
{
	if (sem_trywait(phil->input->fork_sem) == 0)
		print_status(phil, TAKE, start_time);
	else
		return (1);
	if (sem_trywait(phil->input->fork_sem) == 0)
		print_status(phil, TAKE, start_time);
	else
		return (1);
	return (0);
}

static void	returnforks(t_phil *phil)
{
	sem_post(phil->input->fork_sem);
	sem_post(phil->input->fork_sem);
}

void	*living(t_phil *phil)
{
	struct timeval	start;

	sem_wait(phil->input->wait_sem);
	gettimeofday(&start, NULL);
	gettimeofday(&phil->start_eat, NULL);
	if (phil->id % 2 == 0)
		u_sleeper(phil->input->tt_sleep * 1000, phil->input->p_num);
	while (time_diff(phil->start_eat) <= phil->input->tt_die)
	{
		if (takeforks(phil, start))
			break;
		usleep(100);
		print_status(phil, EAT, start);
		gettimeofday(&phil->start_eat, NULL);
		u_sleeper(phil->input->tt_eat * 1000, phil->input->p_num);
		returnforks(phil);
		if (!(--(phil->run_cycle)))
			break ;
		print_status(phil, SLEEP, start);
		u_sleeper(phil->input->tt_sleep * 1000, phil->input->p_num);
		print_status(phil, THINK, start);
	}
	print_status(phil, DEATH, start);
	return (NULL);
}

void	print_status(t_phil *phil, int action, struct timeval s_time)
{
	sem_wait(phil->input->print_sem);
	if (action == THINK)
		printf("%ldms: %d	is thinking.\n", time_diff(s_time), phil->id);
	else if (action == TAKE)
		printf("%ldms: %d	has taken a fork.\n", time_diff(s_time), phil->id);
	else if (action == EAT)
		printf("%ldms: %d	is eating.\n", time_diff(s_time), phil->id);
	else if (action == SLEEP)
		printf("%ldms: %d	is sleeping.\n", time_diff(s_time), phil->id);
	if (action == DEATH)
		printf("%ldms: %d	has passed away.\n", time_diff(s_time), phil->id);
	else
		sem_post(phil->input->print_sem);
}