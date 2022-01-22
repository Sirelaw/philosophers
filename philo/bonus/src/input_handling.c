/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 06:25:49 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/22 22:16:12 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
	if ((ft_atoi(argv[1]) <= 0) || (ft_atoi(argv[2]) < 0) ||
		(ft_atoi(argv[3]) < 0) || (ft_atoi(argv[4]) < 0))
	{
		write(1, "Enter positive values.\n", 23);
		return (3);
	}
	return (0);
}

void	initialize_input(t_input *input, int argc, char **argv)
{
	input->p_num = ft_atoi(argv[1]);
	input->tt_die = ft_atoi(argv[2]);
	input->tt_eat = ft_atoi(argv[3]);
	input->tt_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input->run_cycle = ft_atoi(argv[5]);
	else
		input->run_cycle = -1;
	sem_unlink(PRINT_SEM_FNAME);
	sem_unlink(FORK_SEM_FNAME);
	sem_unlink(WAIT_SEM_FNAME);
	input->print_sem = sem_open(PRINT_SEM_FNAME, O_CREAT, 0666, 1);
	input->fork_sem = sem_open(FORK_SEM_FNAME, O_CREAT, 0666, input->p_num);
	input->wait_sem = sem_open(WAIT_SEM_FNAME, O_CREAT, 0666, 0);
	if ((input->print_sem == SEM_FAILED) || (input->fork_sem == SEM_FAILED) ||
		(input->wait_sem == SEM_FAILED))
	{
		perror("Failed to open semaphore\n");
		exit(EXIT_FAILURE);	
	}
}
