/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 11:24:03 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/13 19:04:44 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	fork_lstadd_back(t_fork **lst, t_fork *new)
{
	t_fork	*p;

	p = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (p->next != NULL)
			p = p->next;
		p->next = new;
	}
}

t_fork	*fork_lstnew(int state, int philo_id, t_input *input)
{
	t_fork	*newelem;

	newelem = malloc(sizeof(t_fork));
	if (newelem == NULL)
		return (NULL);
	pthread_mutex_init(&(newelem->fork_lock), NULL);
	newelem->print_lock = input->print_mutex;
	newelem->state = state;
	newelem->philo_id = philo_id;
	newelem->tt_die = input->tt_die;
	newelem->tt_eat = input->tt_eat;
	newelem->tt_sleep = input->tt_sleep;
	newelem->last_eat = 0;
	newelem->next = NULL;
	return (newelem);
}
