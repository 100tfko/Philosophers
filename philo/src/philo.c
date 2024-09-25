/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:20:57 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/08/12 11:21:00 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

int	ft_mutex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phil_nb)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i += 1;
	}
	if (pthread_mutex_init(&data->meal_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->write_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->dead_lock, NULL))
		return (1);
	return (0);
}

int	ft_init_data(t_data *data, int argc, char **argv)
{
	pthread_mutex_t	*forks;

	data->phil_nb = (int)ft_atoi_long(argv[1]);
	data->time_to_die = (size_t)ft_atoi_long(argv[2]);
	data->time_to_eat = (size_t)ft_atoi_long(argv[3]);
	data->time_to_sleep = (size_t)ft_atoi_long(argv[4]);
	if (argc == 6)
		data->max_eat = (int)ft_atoi_long(argv[5]);
	else
		data->max_eat = -1;
	data->phil_done = 0;
	forks = malloc(sizeof(pthread_mutex_t) * data->phil_nb);
	if (!forks)
		return (1);
	data->forks = forks;
	data->start_time = ft_current_time();
	data->dead = 0;
	if (ft_mutex_init(data))
		return (1);
	return (0);
}

t_philo	*ft_init_philos(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *)malloc(data->phil_nb * sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < data->phil_nb)
	{
		philos[i].thread = 0;
		philos[i].data = data;
		philos[i].id = (i + 1);
		philos[i].last_meal = philos[i].data->start_time;
		philos[i].meals_eaten = 0;
		philos[i].max_eat = data->max_eat;
		philos[i].left_fork = &data->forks[i];
		if (i == 0)
			philos[i].right_fork = &data->forks[data->phil_nb - 1];
		else
			philos[i].right_fork = &data->forks[i - 1];
		philos[i].time_to_die = data->time_to_die;
		philos[i].time_to_eat = data->time_to_eat;
		philos[i].time_to_sleep = data->time_to_sleep;
	}
	return (philos);
}

void	ft_create_threads(t_data *data, t_philo *philos)
{
	int			i;
	pthread_t	overseer;

	i = 0;
	if (pthread_create(&overseer, NULL, &ft_watching, philos) != 0)
		return ;
	while (i < data->phil_nb)
	{
		if (pthread_create
			(&philos[i].thread, NULL, &ft_routine, &philos[i]) != 0)
			return ;
		i += 1;
	}
	i = 0;
	if (pthread_join(overseer, NULL) != 0)
		return ;
	while (i < data->phil_nb)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return ;
		i += 1;
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	philos = 0;
	if (ft_check_arguments(argc, argv))
		return (ft_argument_error());
	if (ft_init_data(&data, argc, argv))
		return (printf("Error initialicing structures"), 1);
	philos = ft_init_philos(&data);
	if (!philos)
	{
		free(data.forks);
		return (printf("Malloc error"), 1);
	}
	ft_create_threads(&data, philos);
	ft_destroy_mutex(&data);
	free(data.forks);
	free (philos);
	return (0);
}
