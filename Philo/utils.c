/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugoncal <lugoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:53:57 by lugoncal          #+#    #+#             */
/*   Updated: 2023/09/18 13:07:02 by lugoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->verify);
	if (philo->data->died != 0 || philo->data->satisf == philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->data->verify);
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	time = gettime() - philo->data->t_start;
	printf("%lld %d %s", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->verify);
	pthread_mutex_unlock(&philo->data->print);
}

long long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_big(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (ft_atoi(argv[i]) > INT_MAX)
			return (1);
	}
	return (0);
}

long	ft_atoi(const char *str)
{
	long	i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * sign);
}

int	ft_num(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '+')
				return (1);
		}
	}
	return (0);
}
