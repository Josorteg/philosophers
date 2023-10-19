/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutina.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:41:06 by josorteg          #+#    #+#             */
/*   Updated: 2023/10/06 18:48:15 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*life(void *arg)
{
	t_philo	*philo;
	int		gg;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->main->mstart);
	pthread_mutex_unlock(&philo->main->mstart);
	if (philo->philo_n % 2 == 1)
	{
		ft_sleep(50, philo->main);
		pthread_mutex_lock(&philo->main->mstart);
		pthread_mutex_unlock(&philo->main->mstart);
	}
	gg = 0;
	while (gg != 1)
	{
		eating(philo);
		pthread_mutex_lock(&philo->main->mfinish);
		gg = philo->main->finish;
		pthread_mutex_unlock(&philo->main->mfinish);
	}
	return ((void *) 0);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	ft_print_line(G, philo, FORK, 0);
	if (philo->main->philo_n == 1)
	{
		while (philo->main->finish == 0)
			ft_sleep(1, philo->main);
		exit(1);
	}
	pthread_mutex_lock(philo->r_fork);
	ft_print_line(G, philo, FORK, 0);
	pthread_mutex_lock(&philo->mutex_t_die);
	philo->t_die = ft_time_pass(philo->main->t_start) + philo->main->time_dead;
	pthread_mutex_unlock(&philo->mutex_t_die);
	if (philo->eat_times_left != 0)
		ft_print_line(Y, philo, EAT, 0);
	times_eaten(philo);
	ft_sleep(philo->main->time_eat, philo->main);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (philo->eat_times_left != 0)
		ft_print_line(B, philo, SLEEP, 0);
	ft_sleep(philo->main->time_dream, philo->main);
	if (philo->eat_times_left != 0)
		ft_print_line(O, philo, THINK, 0);
}

void	control(t_main *main)
{
	int	i;
	int	time;

	i = 0;
	while (i < main->philo_n)
	{
		pthread_mutex_lock(&main->philos[i].mutex_t_die);
		time = main->philos[i].t_die;
		pthread_mutex_unlock(&main->philos[i].mutex_t_die);
		if (ft_time_pass(main->t_start) > time)
		{
			pthread_mutex_lock(&main->mfinish);
			main->finish = 1;
			pthread_mutex_unlock(&main->mfinish);
			ft_print_line(R, &main->philos[i], DEAD, 1);
			break ;
		}
		if (main->eat_n > 0 && control_eat(main) == 1)
			break ;
		i++;
		if (i == main->philo_n)
			i = 0;
		usleep(60);
	}
}

void	times_eaten(t_philo *philo)
{
	if (philo->main->eat_n >= philo->eat_times_left
		&& philo->eat_times_left >= 0)
	{
		philo->eat_times_left--;
		if (philo->eat_times_left == 0)
		{
			pthread_mutex_lock(&philo->main->philo_finish);
			philo->main->eat_n_philo++;
			pthread_mutex_unlock(&philo->main->philo_finish);
		}
	}
}

int	control_eat(t_main	*main)
{
	int	i;
	int	aux;

	i = 0;
	pthread_mutex_lock(&main->philo_finish);
	aux = main->eat_n_philo;
	pthread_mutex_unlock(&main->philo_finish);
	if (aux == main->philo_n)
	{
		pthread_mutex_lock(&main->mfinish);
		main->finish = 1;
		pthread_mutex_unlock(&main->mfinish);
		ft_print_line(R, &main->philos[i], "ha terminado", 1);
		return (1);
	}
	return (0);
}
