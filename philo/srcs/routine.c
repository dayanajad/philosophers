/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbinti-m <dbinti-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:07:38 by dbinti-m          #+#    #+#             */
/*   Updated: 2026/01/20 00:00:00 by dbinti-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}

static void	initial_stagger(t_philo *philo)
{
	long long	margin;

	margin = philo->data->time_to_die - philo->data->time_to_eat
		- philo->data->time_to_sleep;
	if (philo->data->num_philo % 2 == 0 && philo->id % 2 == 0)
		usleep(1000);
	else if (philo->data->num_philo % 2 != 0
		&& margin > philo->data->time_to_eat && philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->data->num_philo == 1)
	{
		print_message(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		return (NULL);
	}
	initial_stagger(philo);
	while (!is_dead(philo))
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
