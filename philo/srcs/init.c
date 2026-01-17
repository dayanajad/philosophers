/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbinti-m <dbinti-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:10:25 by dbinti-m          #+#    #+#             */
/*   Updated: 2026/01/16 16:38:16 by dbinti-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (1);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->must_eat_count = -1;
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	data->dead = 0;
	data->start_time = get_time();
	if (!init_forks(data))
		return (0);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	return (1);
}

int	init_philos(t_philo **philos, t_data *data)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->num_philo);
	if (!*philos)
		return (0);
	i = 0;
	while (i < data->num_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal_time = data->start_time;
		(*philos)[i].data = data;
		(*philos)[i].left_fork = &data->forks[i];
		(*philos)[i].right_fork = &data->forks[(i + 1) % data->num_philo];
		i++;
	}
	return (1);
}
