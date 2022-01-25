/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 20:15:24 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/22 19:58:16 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

static char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	uc;

	uc = (unsigned char) c;
	i = 0;
	while ((s[i] != uc) && (s[i] != '\0'))
		i++;
	if (s[i] == uc)
		return ((char *) &s[i]);
	else
		return (NULL);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	if (str[0] == '\0')
		return (0);
	while (ft_strchr(" \n\t\v\f\r", str[i]))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = (-1);
		i++;
	}
	while ((str[i] > 47) && (str[i] < 58))
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	return (sign * num);
}
