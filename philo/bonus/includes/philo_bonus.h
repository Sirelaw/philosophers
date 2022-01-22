/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:09:11 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/22 23:29:41 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <semaphore.h>

#define PRINT_SEM_FNAME "/printsem"
#define FORK_SEM_FNAME  "/forksem"
#define WAIT_SEM_FNAME "/waitsem"

enum action
{
	THINK,
	TAKE,
	EAT,
	SLEEP,
	DEATH
};

typedef struct	s_input
{
	int				p_num;
	long			tt_die;
	int				tt_eat;
	long			tt_sleep;
	int				run_cycle;
	struct timeval	start;
	sem_t			*print_sem;
	sem_t			*fork_sem;
	sem_t			*wait_sem;
}t_input;

typedef	struct s_phil
{
	t_input			*input;
	int				id;
	int				run_cycle;
	long			last_eat;
	struct timeval	start_eat;
}t_phil;


int		check_bad_input(int argc, char **argv);
int		ft_atoi(const char *str);
t_phil	*new_philo(int id, t_input *input);
void	*living(t_phil *phils);
void	u_sleeper(long	sleep_time, int sleep_duration);
long	time_diff(struct timeval start_time);
void	initialize_input(t_input *input, int argc, char **argv);
void	print_status(t_phil *phil, int action, struct timeval s_time);

#endif