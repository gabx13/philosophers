/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgabovs <vgabovs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:38:55 by vgabovs           #+#    #+#             */
/*   Updated: 2024/06/25 20:39:08 by vgabovs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo, t_fork *fork)
{
	(void)philo;
	pthread_mutex_lock(fork->fork);
	if (fork->taken)
	{
		pthread_mutex_unlock(fork->fork);
		return (0);
	}
	fork->taken = 1;
	pthread_mutex_unlock(fork->fork);
	return (1);
}

int	put_fork(t_philo *philo, t_fork *fork)
{
	(void)philo;
	pthread_mutex_lock(fork->fork);
	fork->taken = 0;
	pthread_mutex_unlock(fork->fork);
	return (1);
}

int	wait_for_forks(t_philo *philo)
{
	int	forks;

	forks = 0;
	while (forks < 2)
	{
		if (check_dead(philo) || stop_func(philo->prog))
			return (1);
		if (take_fork(philo, philo->l_fork))
		{
			print_state(philo, FORK);
			forks++;
		}
		if (philo->r_fork && take_fork(philo, philo->r_fork))
		{
			print_state(philo, FORK);
			forks++;
		}
		usleep(50);
	}
	return (check_dead(philo));
}
