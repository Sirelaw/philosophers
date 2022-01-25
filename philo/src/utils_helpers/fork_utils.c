/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 11:24:03 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/25 00:25:36 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	fork_lstadd_back(t_fork **lst, t_fork *new)
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

static t_fork	*fork_lstnew(int count, int id, t_input *input)
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

static t_fork	*create_single_fork(t_input *input)
{
	t_fork	*first_fork;

	first_fork = fork_lstnew(1, 1, input);
	if (first_fork == NULL)
		return (NULL);
	first_fork->next = first_fork;
	return (first_fork);
}

t_fork	*create_forks(int n, t_input *input)
{
	int		i;
	t_fork	*first_fork;
	t_fork	*temp_fork;

	i = 0;
	if (input->p_num == 1)
		first_fork = create_single_fork(input);
	else
	{
		while (i++ < n)
		{
			if (i == 1)
				first_fork = fork_lstnew(1, i, input);
			else if (i != n)
				fork_lstadd_back(&first_fork, fork_lstnew(1, i, input));
			else if (i == n)
			{
				temp_fork = fork_lstnew(1, i, input);
				fork_lstadd_back(&first_fork, temp_fork);
				temp_fork->next = first_fork;
			}
		}
	}
	return (first_fork);
}
