/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 11:24:03 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/17 15:04:31 by oipadeol         ###   ########.fr       */
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

t_fork	*fork_lstnew(int count, int id, t_input *input)
{
	t_fork	*newelem;

	newelem = malloc(sizeof(t_fork));
	if (newelem == NULL)
		return (NULL);
	newelem->input = input;
	pthread_mutex_init(&(newelem->fork_lock), NULL);
	newelem->id = id;
	newelem->count = count;
	newelem->run_cycle = input->run_cycle;
	newelem->last_eat = 0;
	newelem->next = NULL;
	return (newelem);
}
