/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:55:48 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/08/21 12:56:16 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

void	*ft_watching(void *philo)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)philo;
	i = 0;
	while (!usleep(10))
	{
		i = 0;
		while (i < philos->data->phil_nb)
		{
			pthread_mutex_lock(&philos->data->meal_lock);
			if (ft_check_dead_and_done(&philos[i]))
			{
				pthread_mutex_unlock(&philos->data->meal_lock);
				return (philo);
			}
			i += 1;
			pthread_mutex_unlock(&philos->data->meal_lock);
		}
	}
	return (philo);
}

void	ft_pick_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		ft_msg ("has taken a fork", philo, 0);
		pthread_mutex_lock(philo->left_fork);
		ft_msg ("has taken a fork", philo, 0);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		ft_msg ("has taken a fork", philo, 0);
		pthread_mutex_lock(philo->right_fork);
		ft_msg ("has taken a fork", philo, 0);
	}
}

void	ft_routine2(t_philo *philo)
{
	ft_pick_forks(philo);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = ft_current_time();
	philo->meals_eaten += 1;
	ft_msg ("is eating", philo, 0);
	if (philo->meals_eaten == philo->max_eat)
		philo->data->phil_done += 1;
	pthread_mutex_unlock(&philo->data->meal_lock);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	ft_msg ("is sleeping", philo, 0);
	usleep(philo->time_to_sleep * 1000);
	ft_msg ("is thinking", philo, 0);
	return ;
}

void	ft_one_philo(t_philo *philo)
{
	ft_msg ("has taken a fork", philo, 0);
	usleep(philo->time_to_die * 1000);
	ft_msg ("has died", philo, 1);
}

void	*ft_routine(void *philo)
{
	t_philo	*philos;
	int		flag;

	flag = 0;
	philos = (t_philo *)philo;
	while ((flag == 0) && ((philos->meals_eaten < philos->max_eat)
			|| philos->max_eat < 0))
	{
		if (philos->data->phil_nb == 1)
		{
			ft_one_philo(philos);
			flag = 1;
		}
		else
		{
			ft_routine2(philos);
			pthread_mutex_lock(&philos->data->dead_lock);
			if (philos->data->dead == 1)
				flag = 1;
			pthread_mutex_unlock(&philos->data->dead_lock);
		}
	}
	return (philo);
}
