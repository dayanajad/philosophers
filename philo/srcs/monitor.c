/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbinti-m <dbinti-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:39:08 by dbinti-m          #+#    #+#             */
/*   Updated: 2026/01/17 00:31:11 by dbinti-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philo)
{
	long long	time_since_meal;

	pthread_mutex_lock(&philo->data->eat_lock);
	time_since_meal = get_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->eat_lock);
	if (time_since_meal >= philo->data->time_to_die)
		return (1);
	return (0);
}

static int	all_ate_enough(t_philo *philos, t_data *data)
{
	int	i;

	if (data->must_eat_count == -1)
		return (0);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->eat_lock);
		if (philos[i].meals_eaten < data->must_eat_count)
		{
			pthread_mutex_unlock(&data->eat_lock);
			return (0);
		}
		pthread_mutex_unlock(&data->eat_lock);
		i++;
	}
	return (1);
}

static void	set_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_lock);
}

static void	announce_death(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (!data->dead)
	{
		data->dead = 1;
		pthread_mutex_lock(&data->print_lock);
		printf("%lld %d died\n", get_time() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_lock);
	}
	pthread_mutex_unlock(&data->dead_lock);
}

void	monitor(t_philo *philos, t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->num_philo)
		{
			if (check_death(&philos[i]))
			{
				announce_death(&philos[i], data);
				return ;
			}
			i++;
		}
		if (all_ate_enough(philos, data))
		{
			set_dead(data);
			return ;
		}
		usleep(1000);
	}
}
