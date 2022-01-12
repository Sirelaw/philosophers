/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:43:15 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/12 23:09:49 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/philo.h"

t_fork	*create_forks(int n, t_input *input)
{
	int	i;
	t_fork	*first_fork;
	t_fork	*temp_fork;

	i = 0;
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
	return (first_fork);
}