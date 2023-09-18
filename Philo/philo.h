/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugoncal <lugoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:41:05 by lugoncal          #+#    #+#             */
/*   Updated: 2023/09/18 13:06:36 by lugoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

# define TAKEN "has taken a fork\n"
# define EATING " is eating\n"
# define SLEEPING "is sleeping\n"
# define THINKING "is thinking\n"
# define DIED "died\n"

typedef struct s_philo{
	int				id;
	int				x_eat;
	long long		time_eat;
	pthread_t		philo;
	pthread_mutex_t	alive;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int					n_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
	int					died;
	int					satisf;
	long long			t_start;
	t_philo				*philos;
	pthread_mutex_t		print;
	pthread_mutex_t		verify;
	pthread_mutex_t		*forks;
	pthread_t			control;
}	t_data;

//living.c
int			think(t_philo *philo);
int			slep(t_philo *philo);
int			eat(t_philo *philo);
int			take_fork(t_philo *philo);
void		*living(void *philo_id);

//control.c
int			is_satisfied(t_data *data);
int			is_dead(t_data *data);
void		*control(void *thread);

//create.c
int			join_threads(t_data *data);
int			create_threads(t_data *data);
int			create_philos(t_data *data);
int			create_forks(t_data *data);
int			create(t_data *data);

//utils.c
void		print(t_philo *philo, char *str);
long long	gettime(void);
int			ft_big(int argc, char **argv);
long		ft_atoi(const char *str);
int			ft_num(int argc, char **argv);

//main.c
void		boom(t_data *data);
void		init(t_data *data, char **argv);
int			valid(int argc, char **argv);

#endif
