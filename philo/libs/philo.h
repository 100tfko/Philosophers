/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 09:59:04 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/08/12 10:50:58 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*---------------------------------   LIBS   ---------------------------------*/

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include <stdio.h>

/*--------------------------------   STRUCTS   -------------------------------*/

typedef struct s_data
{
	int				phil_nb;
	int				max_eat;
	int				phil_done;
	int				dead;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
}	t_data;
//un mutex para escribir, para comer, para last meal y taquilla?

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				max_eat;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

/*-------------------------------   FUNCTIONS   ------------------------------*/

//philo: main file
int			main(int argc, char **argv);
void		ft_create_threads(t_data *data, t_philo *philos);
t_philo		*ft_init_philos(t_data *data);
int			ft_init_data(t_data *data, int argc, char **argv);
int			ft_mutex_init(t_data *data);

//routine: main loop for the philosophers threads
void		*ft_routine(void *philo);
void		ft_one_philo(t_philo *philo);
void		ft_routine2(t_philo *philo);
void		ft_pick_forks(t_philo *philo);
void		*ft_watching(void *philo);

// check_arguments: parsing arguments file
int			ft_check_atoi(char **argv);
int			ft_check_arguments(int argc, char **argv);
int			ft_argument_error(void);

//utils: utility functions for bigger functions
int			ft_check_dead_and_done(t_philo *philo);
void		ft_destroy_mutex(t_data *data);
void		ft_msg(char *str, t_philo *philos, int dying);
size_t		ft_current_time(void);
long int	ft_atoi_long(const char *str);

#endif