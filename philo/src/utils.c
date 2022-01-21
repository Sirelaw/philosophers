/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:43:15 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/20 23:53:42 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/philo.h"

t_fork	*create_single_fork(t_input *input)
{
	t_fork	*first_fork;

	first_fork = fork_lstnew(1, 1, input);
	if (first_fork == NULL)
		return (NULL);
	first_fork->next = first_fork;
	if (first_fork == NULL)
		return (NULL);
	return (first_fork);
}

t_fork	*create_forks(int n, t_input *input)
{
	int	i;
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