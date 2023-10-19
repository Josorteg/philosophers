/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:18:26 by josorteg          #+#    #+#             */
/*   Updated: 2023/10/06 12:42:50 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long int	ft_atoi(char *str)
{
	long int	sign;
	long int	num;
	int			leng;

	leng = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
		leng++;
	}
	else if (*str == '+')
		str++;
	num = 0;
	while (48 <= *str && 57 >= *str)
	{
		num = ((*str) - '0') + num * 10;
		str++;
		leng++;
	}
	if (leng > 13 || (num * sign > 2147483647 || num * sign < -2147483648))
		return (-1);
	return (num * sign);
}

int	ft_check(int argv, char **args)
{
	int	i;
	int	j;

	i = 1;
	while (i < argv)
	{
		j = 0;
		if (ft_strlen(args[i]) < 1)
			return (1);
		while (args[i][j])
		{
			if ((args[i][j] < 9 || args[i][j] > 13) && args[i][j] != 32
				&& (args[i][j] < '0' || args[i][j] > '9'))
				return (1);
			j++;
		}
		if (ft_atoi(args[i]) < 1)
			return (1);
		i++;
	}
	return (0);
}
