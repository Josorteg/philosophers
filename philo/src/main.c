/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:32:11 by josorteg          #+#    #+#             */
/*   Updated: 2023/10/06 11:13:10 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argv, char **args)
{
	t_main	main;

	if (argv < 5 || argv > 6)
	{
		printf("5 o 6 argumentos");
		return (1);
	}
	if (ft_check(argv, args) == 1)
	{
		printf("argumentos numericos positivos");
		return (1);
	}
	if (ft_main_init(&main, args) != 0)
		return (1);
	ft_sleep(100, &main);
	gettimeofday(&main.t_start, NULL);
	pthread_mutex_unlock(&main.mstart);
	control(&main);
	ft_finish(&main);
	return (0);
}
