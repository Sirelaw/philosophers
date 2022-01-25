/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:59:10 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/25 00:09:52 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	u_sleeper(long	sleep_time, int sleep_duration)
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
		usleep(sleep_duration);
	}
	return ;
}

long	time_diff(struct timeval start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((current_time.tv_sec - start_time.tv_sec) * 1000)
		+ ((current_time.tv_usec - start_time.tv_usec) / 1000));
}
