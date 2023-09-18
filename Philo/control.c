/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugoncal <lugoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:36:52 by lugoncal          #+#    #+#             */
/*   Updated: 2023/09/18 13:06:45 by lugoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_satisfied(t_data *data)
{
	pthread_mutex_lock(&data->verify);
	if (data->satisf == data->n_philo)
	{
		pthread_mutex_unlock(&data->verify);
		return (1);
	}
	pthread_mutex_unlock(&data->verify);
	return (0);
}

int	is_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&data->philos[i].alive);
		if (gettime() - data->philos[i].time_eat > data->t_die)
		{
			print(&data->philos[i], DIED);
			pthread_mutex_lock(&data->verify);
			data->died++;
			pthread_mutex_unlock(&data->verify);
			pthread_mutex_unlock(&data->philos[i].alive);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].alive);
		i++;
	}
	return (0);
}

void	*control(void *thread)
{
	t_data	*data;

	data = (t_data *)thread;
	while (1)
	{
		if (is_dead(data) != 0)
			return (NULL);
		if (data->n_eat != 0)
			if (is_satisfied(data) != 0)
				return (NULL);
	}
}
