/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:29:45 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/25 12:47:52 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	free_all(t_input *input)
{
	sem_close(input->print_sem);
	sem_close(input->fork_sem);
	sem_close(input->wait_sem);
	sem_close(input->done_sem);
	free(input);
}

void	wait_and_kill(t_input *input, pid_t *pid_arr, t_phil **phil)
{
	int	i;

	i = 0;
	sem_wait(input->done_sem);
	usleep(input->tt_eat * 1000);
	while (i < input->p_num)
		kill(pid_arr[i++], SIGINT);
	i = 0;
	while (i < input->p_num)
		free(phil[i++]);
	free(pid_arr);
	free(phil);
}

t_phil	**create_phils(t_input *input, int n)
{
	t_phil	**phil;
	int		i;

	phil = malloc(n * sizeof(t_phil *));
	i = 0;
	while (i++ < n)
		phil[i - 1] = new_philo(i, input);
	return (phil);
}

void	*start_routine(t_input *input)
{
	int				i;
	pid_t			pid;
	pid_t			*pid_arr;
	t_phil			**phil;
	struct timeval	s_time;

	i = 0;
	pid = 1;
	pid_arr = malloc(input->p_num * sizeof(pid_t));
	phil = create_phils(input, input->p_num);
	gettimeofday(&s_time, NULL);
	while ((i++ < input->p_num) && (pid != 0))
	{
		pid = fork();
		if (pid == -1)
			return (NULL);
		pid_arr[i] = pid;
		if (pid == 0)
			philo_routine(phil[i - 1], s_time);
	}
	wait_and_kill(input, pid_arr, phil);
	return (0);
}

int	main(int argc, char **argv)
{
	t_input		*input;

	if (check_bad_input(argc, argv))
		return (1);
	input = malloc(sizeof(t_input));
	initialize_input(input, argc, argv);
	start_routine(input);
	free_all(input);
	return (0);
}
