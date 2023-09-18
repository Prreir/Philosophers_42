/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugoncal <lugoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:04:40 by lugoncal          #+#    #+#             */
/*   Updated: 2023/09/18 13:10:07 by lugoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->philos[i].philo, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join(data->control, NULL) != 0)
		return (1);
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philos[i].philo, NULL, \
		&living, &data->philos[i]) != 0)
			return (1);
		usleep(2000);
		i++;
	}
	if (pthread_create(&data->control, NULL, &control, data) != 0)
		return (1);
	return (0);
}

int	create_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].x_eat = 0;
		data->philos[i].time_eat = gettime();
		data->philos[i].r_fork = &data->forks[i];
		if (i == (data->n_philo - 1))
			data->philos[i].l_fork = &data->forks[0];
		else
			data->philos[i].l_fork = &data->forks[i + 1];
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].alive, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	create_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * (data->n_philo));
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->verify, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (1);
	return (0);
}

int	create(t_data *data)
{
	if (create_forks(data) != 0)
		return (printf("An error has occurred!\n"));
	if (create_philos(data) != 0)
		return (printf("An error has occurred!\n"));
	if (create_threads(data) != 0)
		return (printf("An error has occurred!\n"));
	if (join_threads(data) != 0)
		return (printf("An error has occurred!\n"));
	return (0);
}
