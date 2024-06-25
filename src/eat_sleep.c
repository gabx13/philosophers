/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgabovs <vgabovs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:40:57 by vgabovs           #+#    #+#             */
/*   Updated: 2024/06/25 21:07:17 by vgabovs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo, t_prog *prog)
{
	print_state(philo, EAT);
	philo->last_eat = get_current_time();
	philo->times_ate++;
	if (ft_usleep(prog->time_to_eat, philo))
		return (1);
	put_fork(philo, philo->l_fork);
	put_fork(philo, philo->r_fork);
	return (check_dead(philo));
}

int	philo_sleep(t_philo *philo, t_prog *prog)
{
	pthread_mutex_lock(&prog->print);
	if (philo->times_ate == prog->num_of_meals)
		prog->full_philos++;
	pthread_mutex_unlock(&prog->print);
	print_state(philo, SLEEP);
	if (ft_usleep(prog->time_to_sleep, philo))
		return (1);
	return (check_dead(philo));
}
