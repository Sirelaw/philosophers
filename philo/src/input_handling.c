/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 06:25:49 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/10 17:29:35 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_bad_input(int argc, char **argv)
{
	if ((argc != 5) && (argc != 6))
	{
		write(1, "***************************************************\n", 52);
		write(1, "*       Enter the required set of arguments.      *\n", 52);
		write(1, "* Input should have the following format in msecs.*\n", 52);
		write(1, "*$>./philo philos_no die eat sleep [no_of_eats]   *\n", 52);
		write(1, "***************************************************\n", 52);
		return(1);
	}
	if (argc == 6)
		if (ft_atoi(argv[5]) <= 0)
		{
			write(1, "Enter a number greater than 0 for [no_of_eats]\n", 47);
			return(2);
		}
	return (0);
}
