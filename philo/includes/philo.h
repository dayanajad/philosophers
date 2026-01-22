/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbinti-m <dbinti-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 22:43:08 by dbinti-m          #+#    #+#             */
/*   Updated: 2026/01/16 22:50:40 by dbinti-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <time.h>
# include <errno.h>

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				dead;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
}	t_data;

typedef struct s_philo
{
	int				id;
	long long		last_meal_time;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

//	srcs/utils.c

int			ft_atoi(const char *str);
long long	get_time(void);
void		ft_usleep(long long time);
void		print_message(t_philo *philo, char *msg);

// srcs/init.c
int			init_data(t_data *data, int ac, char **av);
int			init_philos(t_philo **philos, t_data *data);

// srcs/monitor.c

void		monitor(t_philo *philos, t_data *data);

// srcs/routine.c

void		*routine(void *arg);

// srcs/actions.c

void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

#endif
