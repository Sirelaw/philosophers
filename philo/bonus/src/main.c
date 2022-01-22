/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:29:45 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/22 22:34:23 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	free_all(t_input *input)
{
	sem_close(input->print_sem);
	sem_close(input->fork_sem);
	sem_close(input->wait_sem);
	free(input);
}

// void	join_or_detach_threads(pthread_t *philos, int n, void **watch_ret)
// {
// 	int i;
// 	int *ret;
// 	i = 0;
// 	ret = (int *)*watch_ret;
// 	if (*ret == 1)
// 		while (i++ < n)
// 			pthread_detach(philos[i]);
// 	else
// 		while (i++ <= n)
// 			pthread_join(philos[i], NULL);
// 	free(*watch_ret);
// }

// void	*watchdog(void *forks)
// {
// 	t_phil			*phil;
// 	struct timeval	start;
// 	long			tt_die;
// 	int				*ret;

// 	phil = forks;
// 	ret = malloc(sizeof(int));
// 	*ret = 0;
// 	tt_die = phil->input->tt_die;
// 	while (phil->input->wait_int == 0)
// 		usleep(2);
// 	u_sleeper(phil->input->tt_die, phil->input->p_num);
// 	while ((time_diff(phil->start_eat) <= tt_die) && phil->run_cycle)
// 		phil = phil->next;
// 	if (!(phil->run_cycle))
// 		return ((void *)ret);
// 	else
// 		print_status(phil, DEATH, phil->input->start);
// 	*ret = 1;
// 	return (ret);
// }

void	*start_routine(t_input *input)
{
	int		i;
	pid_t	pid;
	t_phil	*phil;

	i = 0;
	pid = 1;
	while ((i++ < input->p_num) && (pid != 0))
	{
		pid = fork();
		if (pid == 0)
		{
			phil = new_philo(i, input);
			living(phil);
			break ;
		}
	}
	i = 0;
	while (i++ < input->p_num)
		sem_post(input->wait_sem);
	i = 0;
	while (i++ < input->p_num)	
		wait(NULL);
	return (0);
}

int main(int argc, char **argv)
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