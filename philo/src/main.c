/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:00:46 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/21 22:47:32 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	u_sleeper(long	sleep_time)
{
	struct timeval	start_time;
	struct timeval	current_time;
	long			timediff;
	
	gettimeofday(&start_time, NULL);
	timediff = 0;
	while (timediff < sleep_time)
	{
		gettimeofday(&current_time, NULL);
		timediff = ((current_time.tv_sec - start_time.tv_sec) * 1000000)
				+ ((current_time.tv_usec - start_time.tv_usec));
		usleep(200);
	}
	return ;
}

void	free_all(t_input *input, t_fork *forks)
{
	t_fork	*one_fork;
	t_fork	*temp;

	one_fork = forks->next;
	temp = forks->next;
	pthread_mutex_destroy(&(input->print_lock));
	free(input);
	pthread_mutex_destroy(&(forks->fork_lock));
	free(forks);
	while (temp != forks)
	{
		temp = temp->next;
		pthread_mutex_destroy(&(one_fork->fork_lock));
		free(one_fork);
		one_fork = temp;
	}
}

void	join_or_detach_threads(pthread_t *philos, int n, void **watch_ret)
{
	int i;
	int *ret;
	i = 0;
	ret = (int *)*watch_ret;
	if (*ret == 1)
		while (i++ < n)
			pthread_detach(philos[i]);
	else
		while (i++ <= n)
			pthread_join(philos[i], NULL);
	free(*watch_ret);
}

void	initialize_input(t_input *input, int argc, char **argv)
{
	input->wait_int = 0;
	input->p_num = ft_atoi(argv[1]);
	input->tt_die = ft_atoi(argv[2]);
	input->tt_eat = ft_atoi(argv[3]);
	input->tt_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input->run_cycle = ft_atoi(argv[5]);
	else
		input->run_cycle = -1;
	pthread_mutex_init(&(input->print_lock), NULL);
}

long	time_diff(struct timeval start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - start_time.tv_sec) * 1000)
		+ ((current_time.tv_usec - start_time.tv_usec) / 1000);
}

long	time_diff_2(struct timeval start_time, struct timeval start_eat)
{
	
	return ((start_eat.tv_sec - start_time.tv_sec) * 1000)
		+ ((start_eat.tv_usec - start_time.tv_usec) / 1000);
}

void	print_status(t_fork *phil, int action, struct timeval s_time)
{
	pthread_mutex_lock(&(phil->input->print_lock));
	if (action == THINK)
		printf("%ldms: %d	is thinking.\n", time_diff(s_time), phil->id);
	else if (action == TAKE)
		printf("%ldms: %d	has taken a fork.\n", time_diff(s_time), phil->id);
	else if (action == EAT)
		printf("%ldms: %d	is eating.\n", time_diff(s_time), phil->id);
	else if (action == SLEEP)
		printf("%ldms: %d	is sleeping.\n", time_diff(s_time), phil->id);
	if (action == DEATH)
		printf("%ldms: %d	has passed away.\n", time_diff(s_time), phil->id);
	else
		pthread_mutex_unlock(&(phil->input->print_lock));
}

int	takeforks(t_fork *forks, struct timeval start_time)
{
	t_fork	*nextfork;

	nextfork = forks->next;
	if (pthread_mutex_lock((&(forks->fork_lock))) == 0)
	{
		(forks->count)--;
		print_status(forks, TAKE, start_time);
	}
	if (pthread_mutex_lock((&(nextfork->fork_lock))) == 0)
	{
		if (nextfork->count == 1)
		{
			(nextfork->count)--;
			print_status(forks, TAKE, start_time);
			return(0);
		}
		u_sleeper(forks->input->tt_die * 1000);
	}
	return (1);
}

int	returnforks(t_fork *forks)
{
	t_fork	*nextfork;

	nextfork = forks->next;
	(forks->count)++;
	pthread_mutex_unlock(&(forks->fork_lock));
	(nextfork->count)++;
	pthread_mutex_unlock(&(nextfork->fork_lock));
	return(1);
}

void	half_think(t_fork *forks, struct timeval start_time)
{
	if (forks->id % 2 == 0)
	{
		print_status(forks, THINK, start_time);
		usleep(forks->input->tt_eat * 1000);
	}
}

void	*living(void *forks)
{
	t_fork			*phil;
	struct timeval	start;

	phil = forks;
	while (phil->input->wait_int == 0)
		usleep(1);
	start = phil->input->start;
	gettimeofday(&(phil->start_eat), NULL);
	half_think(phil, start);
	while (1)
	{
		if (takeforks(phil, start))
			break ;
		print_status(phil, EAT, start);
		gettimeofday(&(phil->start_eat), NULL);
		u_sleeper(phil->input->tt_eat * 1000);
		returnforks(phil);
		u_sleeper(1);
		if (!(--(phil->run_cycle)))
			break ;
		print_status(phil, SLEEP, start);
		u_sleeper(phil->input->tt_sleep * 1000);
		print_status(phil, THINK, start);
	}
	return (NULL);
}

void	*watcher(void *forks)
{
	t_fork			*phil;
	struct timeval	start;
	long			tt_die;
	int				*ret;

	phil = forks;
	ret = malloc(sizeof(int));
	*ret = 0;
	tt_die = phil->input->tt_die;
	while (phil->input->wait_int == 0)
		usleep(2);
	u_sleeper(phil->input->tt_die);
	while ((time_diff(phil->start_eat) <= tt_die) && phil->run_cycle)
		phil = phil->next;
	if (!(phil->run_cycle))
		return ((void *)ret);
	else
		print_status(phil, DEATH, phil->input->start);
	*ret = 1;
	return (ret);
}

void	*start_routine(t_input *input, t_fork *forks, pthread_t *philos)
{
	int			i;
	void		*watch_ret;
	pthread_t	watchdog;

	i = 0;
	if (pthread_create(&watchdog, NULL, &watcher, forks) != 0)
			return (NULL);
	while (i++ < input->p_num)
	{
		if (pthread_create(philos + i, NULL, &living, forks) != 0)
			return (NULL);
		forks = forks->next;
		u_sleeper(100);
	}
	input->wait_int = 1;
	gettimeofday(&(input->start), NULL);
	pthread_join(watchdog, &watch_ret);
	join_or_detach_threads(philos, input->p_num, &watch_ret);
	free(philos);
	return (0);
}

int main(int argc, char **argv)
{
	t_input		*input;
	t_fork		*first_fork;
	pthread_t	*philos;

	if (check_bad_input(argc, argv))
		return (1);
	input = malloc(sizeof(t_input));
	initialize_input(input, argc, argv);
	first_fork = create_forks(input->p_num, input);
	if (first_fork == NULL)
		return (3);
	philos = malloc(sizeof(pthread_t) * input->p_num);
	if (philos == NULL)
		return (4);
	start_routine(input, first_fork, philos);
	free_all(input, first_fork);
	return (0);
}
