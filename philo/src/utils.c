/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:58:59 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/08/21 12:59:02 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

int	ft_check_dead_and_done(t_philo *philo)
{
	if (philo->data->phil_done == philo->data->phil_nb)
		return (1);
	if (((ft_current_time() - philo->last_meal) > philo->time_to_die + 1)
		&& (philo->meals_eaten != philo->max_eat))
	{
		ft_msg ("has died", philo, 1);
		return (1);
	}
	return (0);
}

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phil_nb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i += 1;
	}
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
}

long int	ft_atoi_long(const char *str)
{
	int			i;
	long int	sign;
	long int	ret;

	i = 0;
	sign = 1;
	ret = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i += 1;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign *= -1;
		i += 1;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		ret = (str[i] - 48) + (ret * 10);
		i += 1;
	}
	return (ret * sign);
}

size_t	ft_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_msg(char *str, t_philo *philos, int dying)
{
	size_t	time;

	pthread_mutex_lock(&philos->data->write_lock);
	time = ft_current_time() - philos->data->start_time;
	pthread_mutex_lock(&philos->data->dead_lock);
	if (philos->data->dead != 1)
		printf("%zu %d %s\n", time, philos->id, str);
	if (dying == 1)
		philos->data->dead = 1;
	pthread_mutex_unlock(&philos->data->dead_lock);
	pthread_mutex_unlock(&philos->data->write_lock);
}
