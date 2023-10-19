/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:32:52 by josorteg          #+#    #+#             */
/*   Updated: 2023/10/06 13:13:46 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

// ================================= COLORS ================================= /

# define E "\033[m"        //end
# define R "\033[1;31m"    //red
# define G "\033[1;32m"    //green
# define Y "\033[1;33m"    //yellow
# define B "\033[1;34m"    //blue
# define T "\033[1;35m"	   //Turquesa
# define C "\033[1;36m"    //Cyan
# define O "\033[38;5;208m" //orange
# define F "\033[38;5;128m"  //purple

// ================================= MESSAGES =============================== //

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

typedef struct s_philo	t_philo;

typedef struct s_main
{
	int				philo_n;
	int				time_dead;
	int				time_eat;
	int				time_dream;
	int				eat_n;
	int				finish;
	int				eat_n_philo;
	struct timeval	t_start;
	struct s_philo	*philos;
	pthread_t		*threads;
	pthread_mutex_t	mprint;
	pthread_mutex_t	mstart;
	pthread_mutex_t	mfinish;
	pthread_mutex_t	philo_finish;
}	t_main;
struct s_philo
{
	int					philo_n;
	int					t_die;
	int					eat_times_left;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		mutex_t_die;
	struct s_main		*main;
};

int			ft_check(int argv, char **args);
long int	ft_atoi(char *str);
int			ft_main_init(t_main *main, char **args);
void		ft_init_threads(t_main	*main);
long		ft_time_pass(struct timeval t_start);

void		ft_init_philos(t_main *main);
void		*life(void *arg);
void		eating(t_philo *philo);

void		control(t_main *main);
int			control_eat(t_main	*main);
void		ft_finish(t_main	*main);
void		times_eaten(t_philo *philo);

void		ft_print_line(char *color, t_philo *aux, char *s, int n);
int			ft_sleep(int millisec, t_main *main);
int			ft_sleep_start(int millisec, t_main *main);

#endif
