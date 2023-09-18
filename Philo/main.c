/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugoncal <lugoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:41:12 by lugoncal          #+#    #+#             */
/*   Updated: 2023/09/18 13:06:54 by lugoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	boom(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].alive);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->verify);
}

void	init(t_data *data, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->n_eat = ft_atoi(argv[5]);
	else
		data->n_eat = 0;
	data->t_start = gettime();
	data->died = 0;
	data->satisf = 0;
}

int	valid(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Check number of arguments!\n");
		return (1);
	}
	if (ft_num(argc, argv) != 0)
	{
		printf("Error: Arguments must be only positive numbers!\n");
		return (1);
	}
	if (ft_big(argc, argv) != 0)
	{
		printf("Error: The numbers are to big!\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (valid(argc, argv) != 0)
		return (0);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		printf("An error has occurred!\n");
	init(data, argv);
	create(data);
	boom(data);
	free(data->philos);
	free(data->forks);
	free(data);
	return (0);
}
