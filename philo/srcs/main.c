/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbinti-m <dbinti-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:14:38 by dbinti-m          #+#    #+#             */
/*   Updated: 2026/01/16 17:56:06 by dbinti-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (0);
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

static void	start_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
}

static void	join_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

static void	cleanup(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->eat_lock);
	pthread_mutex_destroy(&data->dead_lock);
	free(data->forks);
	free(philos);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	if (!valid_args(ac, av))
		return (printf("Error: Invalid arguments\n"), 1);
	if (!init_data(&data, ac, av))
		return (printf("Error: Init failed\n"), 1);
	if (!init_philos(&philos, &data))
		return (free(data.forks), printf("Error: Init failed\n"), 1);
	start_threads(philos, &data);
	monitor(philos, &data);
	join_threads(philos, &data);
	cleanup(philos, &data);
	return (0);
}
