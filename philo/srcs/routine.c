/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbinti-m <dbinti-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:07:38 by dbinti-m          #+#    #+#             */
/*   Updated: 2026/01/17 18:35:31 by dbinti-m         ###   ########.fr       */
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

static void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->eat_lock);
	print_message(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	ft_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

static void	think(t_philo *philo)
{
	long long	think_time;

	print_message(philo, "is thinking");
	if (philo->data->num_philo % 2 != 0 && philo->data->num_philo <= 5)
	{
		think_time = (philo->data->time_to_die - philo->data->time_to_eat
						- philo->data->time_to_sleep) / 2;
		if (think_time > 0)
			ft_usleep(think_time);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		window;

	philo = (t_philo *) arg;
	if (philo->data->num_philo == 1)
	{
		print_message(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		return (NULL);
	}
	if (philo->data->num_philo % 2 != 0 && philo->data->num_philo <= 5)
	{
		if (philo->id % 2 == 0)
			ft_usleep(philo->data->time_to_eat);
	}
	else if (philo->data->num_philo <= 30)
	{
		if (philo->id % 2 == 0)
			usleep(1000);
	}
	else
	{
		window = philo->data->time_to_die - philo->data->time_to_eat
			- philo->data->time_to_sleep;
		if (philo->data->num_philo % 2 == 0 && window >= 10
			&& philo->id % 2 == 0)
			usleep(500);
		else if (philo->data->num_philo % 2 != 0 && window >= 200
			&& philo->id % 2 == 0)
			usleep(500);
	}
	while (!is_dead(philo))
	{
		think(philo);
		eat(philo);
		ft_sleep(philo);
	}
	return (NULL);
}
