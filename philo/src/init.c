/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:22:27 by josorteg          #+#    #+#             */
/*   Updated: 2023/10/06 10:54:02 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_main_init(t_main *main, char **args)
{
	main->finish = 0;
	main->eat_n_philo = 0;
	main->philo_n = ft_atoi(args[1]);
	main->time_dead = ft_atoi(args[2]);
	main->time_eat = ft_atoi(args[3]);
	main->time_dream = ft_atoi(args[4]);
	main->eat_n = -1;
	if (args[5])
		main->eat_n = ft_atoi(args[5]);
	pthread_mutex_init(&main->mstart, NULL);
	pthread_mutex_init(&main->mfinish, NULL);
	pthread_mutex_init(&main->philo_finish, NULL);
	pthread_mutex_init(&main->mprint, NULL);
	main->philos = malloc(main->philo_n * sizeof(t_philo));
	if (!main->philos)
		return (1);
	main->threads = malloc(main->philo_n * sizeof(pthread_t));
	if (!main->threads)
	{
		free(main->philos);
		return (1);
	}
	ft_init_philos (main);
	ft_init_threads(main);
	return (0);
}

void	ft_init_philos(t_main *main)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&main->mstart);
	while (i < main->philo_n)
	{
		main->philos[i].philo_n = i;
		main->philos[i].t_die = main->time_dead;
		main->philos[i].eat_times_left = main->eat_n;
		if (i == 0)
			main->philos[i].r_fork
				= &main->philos[main->philo_n - 1].l_fork;
		else
			main->philos[i].r_fork = &main->philos[i - 1].l_fork;
		pthread_mutex_init(main->philos[i].r_fork, NULL);
		pthread_mutex_init(&main->philos[i].l_fork, NULL);
		pthread_mutex_init(&main->philos[i].mutex_t_die, NULL);
		main->philos[i].main = main;
		i++;
	}
}

void	ft_init_threads(t_main	*main)
{
	int	i;

	i = 0;
	while (i < main->philo_n)
	{
		pthread_create(&main->threads[i], NULL, &life, &main->philos[i]);
		i++;
	}
}
