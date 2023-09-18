/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugoncal <lugoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:23:45 by lugoncal          #+#    #+#             */
/*   Updated: 2023/09/18 13:06:50 by lugoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->verify);
	if (philo->data->died != 0 || philo->data->satisf == philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->data->verify);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->verify);
	print(philo, THINKING);
	return (0);
}

int	slep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->verify);
	if (philo->data->died != 0 || philo->data->satisf == philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->data->verify);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->verify);
	print(philo, SLEEPING);
	usleep(philo->data->t_sleep * 1000);
	return (0);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->verify);
	if (philo->data->died != 0 || philo->data->satisf == philo->data->n_philo)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->data->verify);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->verify);
	pthread_mutex_lock(&philo->alive);
	print(philo, EATING);
	philo->time_eat = gettime();
	pthread_mutex_lock(&philo->data->verify);
	if (philo->data->n_eat != 0)
	{
		philo->x_eat++;
		if (philo->x_eat == philo->data->n_eat)
			philo->data->satisf++;
	}
	pthread_mutex_unlock(&philo->data->verify);
	pthread_mutex_unlock(&philo->alive);
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->verify);
	if (philo->data->died != 0 || philo->data->satisf == philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->data->verify);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->verify);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print(philo, TAKEN);
		pthread_mutex_lock(philo->l_fork);
		print(philo, TAKEN);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print(philo, TAKEN);
		pthread_mutex_lock(philo->r_fork);
		print(philo, TAKEN);
	}
	return (0);
}

void	*living(void *philo_id)
{
	t_philo	*philo;

	philo = (t_philo *)philo_id;
	if (philo->data->n_philo == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		print(philo, TAKEN);
		pthread_mutex_unlock(philo->r_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(2000);
	while (1)
	{
		if (take_fork(philo) != 0)
			return (NULL);
		if (eat(philo) != 0)
			return (NULL);
		if (slep(philo) != 0)
			return (NULL);
		if (think(philo) != 0)
			return (NULL);
	}
}
