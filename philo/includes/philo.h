/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:01:44 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/13 19:03:02 by oipadeol         ###   ########.fr       */
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

typedef struct	s_input
{
	int				p_num;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				no_cycle;
	pthread_mutex_t	print_mutex;
}t_input;

typedef	struct s_fork
{
	pthread_mutex_t	fork_lock;
	pthread_mutex_t	print_lock;
	int				philo_id;
	int 			state;
	void			*next;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				no_cycle;
	long int		last_eat;
}t_fork;


int	check_bad_input(int argc, char **argv);
int	ft_atoi(const char *str);
void	fork_lstadd_back(t_fork **lst, t_fork *new);
t_fork	*fork_lstnew(int state, int philo_id, t_input *input);
t_fork	*create_forks(int n, t_input *input);

#endif
