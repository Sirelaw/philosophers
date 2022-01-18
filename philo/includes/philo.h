/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:01:44 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/18 21:15:45 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

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
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				run_cycle;
	int				wait_int;
	int				dead;
	pthread_mutex_t	print_lock;
}t_input;

typedef	struct s_fork
{
	void			*next;
	t_input			*input;
	pthread_mutex_t	fork_lock;
	int				id;
	int				run_cycle;
	int 			count;
	long			last_eat;
	struct timeval	start_eat;
}t_fork;


int	check_bad_input(int argc, char **argv);
int	ft_atoi(const char *str);
void	fork_lstadd_back(t_fork **lst, t_fork *new);
t_fork	*fork_lstnew(int state, int id, t_input *input);
t_fork	*create_forks(int n, t_input *input);

#endif
