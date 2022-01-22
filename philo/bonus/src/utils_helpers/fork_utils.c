/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 11:24:03 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/22 20:45:56 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

t_phil	*new_philo(int id, t_input *input)
{
	t_phil	*newelem;

	newelem = malloc(sizeof(t_phil));
	if (newelem == NULL)
		return (NULL);
	newelem->input = input;
	newelem->id = id;
	newelem->run_cycle = input->run_cycle;
	newelem->last_eat = 0;
	return (newelem);
}

