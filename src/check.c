/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgabovs <vgabovs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:37:24 by vgabovs           #+#    #+#             */
/*   Updated: 2024/06/25 21:07:07 by vgabovs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->print);
	if (philo->prog->time_to_die <= (long)get_current_time() - philo->last_eat)
	{
		pthread_mutex_unlock(&philo->prog->print);
		print_state(philo, DEAD);
		pthread_mutex_lock(&philo->prog->print);
		philo->prog->dead = 1;
		pthread_mutex_unlock(&philo->prog->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->prog->print);
	return (0);
}

int	stop_func(t_prog *prog)
{
	pthread_mutex_lock(&prog->print);
	if (prog->dead || (prog->num_of_meals != -1
			&& prog->full_philos == prog->num_of_philos))
	{
		pthread_mutex_unlock(&prog->print);
		return (1);
	}
	pthread_mutex_unlock(&prog->print);
	return (0);
}

int	program_check(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf("Error: Wrong number of arguments\n"), 1);
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > MAX_PHILOS)
		return (printf("Error: Wrong number of philosophers\n"), 1);
	if (ft_atoi(argv[2]) < 10 || ft_atoi(argv[3]) < 10 || ft_atoi(argv[4]) < 10)
		return (printf("Error: Time must be at least 10\n"), 1);
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (printf("Error: Number of meals must be at least 1\n"), 1);
	return (0);
}

int	ft_usleep(int time, t_philo *philo)
{
	int	start;

	start = (int)get_current_time();
	while (((int)get_current_time() - start) < time)
	{
		if (check_dead(philo))
			return (1);
		usleep(500);
	}
	return (0);
}
