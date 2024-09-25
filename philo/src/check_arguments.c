/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:17:13 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/08/21 12:17:15 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

int	ft_argument_error(void)
{
	printf("Error: arguments\n");
	printf("Arguments must be in the followinf format:\n");
	printf("[number_of_philosophers] [time_to_die] [time_to_eat]");
	printf("[time_to_sleep]\n");
	printf("optional fifth argument can be accepted as");
	printf(" [number_of_times_each_philosopher_must_eat\n");
	printf("-Note: all arguments must fit in an int and be positive\n");
	return (1);
}

int	ft_check_atoi(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi_long(argv[i]) > INT_MAX || ft_atoi_long(argv[i]) <= 0)
			return (1);
		i += 1;
	}
	return (0);
}

int	ft_check_arguments(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc < 5 || argc > 6)
		return (1);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j += 1;
		}
		i += 1;
	}
	if (ft_check_atoi (argv))
		return (1);
	return (0);
}
