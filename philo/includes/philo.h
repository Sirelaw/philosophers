/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:01:44 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/25 04:46:20 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

enum e_action
{
	THINK,
	TAKE,
	EAT,
	SLEEP,
	DEATH
};

typedef struct s_input
{
	int				p_num;
	long			tt_die;
	int				tt_eat;
	long			tt_sleep;
	int				run_cycle;
	int				wait_int;
	struct timeval	start;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	wait_mutex;
}t_input;

typedef struct s_fork
{
	void			*next;
	t_input			*input;
	pthread_mutex_t	fork_lock;
	int				id;
	int				run_cycle;
	int				count;
	long			last_eat;
	struct timeval	start_eat;
}t_fork;

int		check_bad_input(int argc, char **argv);
int		ft_atoi(const char *str);
t_fork	*create_forks(int n, t_input *input);
void	*living(void *forks);
void	u_sleeper(long	sleep_time, int sleep_duration);
long	time_diff(struct timeval start_time);
void	initialize_input(t_input *input, int argc, char **argv);
void	print_status(t_fork *phil, int action, struct timeval s_time);

#endif
