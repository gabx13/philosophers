/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgabovs <vgabovs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:17:04 by vgabovs           #+#    #+#             */
/*   Updated: 2024/06/25 21:01:21 by vgabovs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_prog(t_prog *prog, int argc, char **argv)
{
	prog->num_of_philos = ft_atoi(argv[1]);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		prog->num_of_meals = ft_atoi(argv[5]);
	else
		prog->num_of_meals = -1;
	prog->dead = 0;
	prog->full_philos = 0;
	prog->start_time = get_current_time();
	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->num_of_philos);
	if (!prog->forks)
		return (1);
	prog->philos = malloc(sizeof(t_philo) * prog->num_of_philos);
	if (!prog->philos)
	{
		free(prog->forks);
		return (1);
	}
	pthread_mutex_init(&prog->print, NULL);
	return (0);
}

void	init_forks(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philos)
	{
		pthread_mutex_init(&prog->forks[i], NULL);
		i++;
	}
}

t_fork	*new_fork(t_philo *philo, int i)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->fork = &philo->prog->forks[i];
	fork->taken = 0;
	return (fork);
}

int	init_philo(t_philo *philo, t_prog *prog)
{
	int	i;

	init_forks(prog);
	i = 0;
	while (i < prog-> num_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].times_ate = 0;
		philo[i].last_eat = prog->start_time;
		philo[i].prog = prog;
		philo[i].l_fork = new_fork(&philo[i], i);
		i++;
	}
	i = 0;
	while (i < prog->num_of_philos)
	{
		philo[i].r_fork = philo[(i + 1) % prog->num_of_philos].l_fork;
		i++;
	}
	if (i == 1)
		philo[0].r_fork = NULL;
	return (0);
}

void	free_all(t_prog *prog, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philos)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		i++;
	}
	i = 0;
	while (i < prog->num_of_philos)
	{
		free(philo[i].l_fork);
		i++;
	}
	pthread_mutex_destroy(&prog->print);
	free(prog->forks);
	free(prog->philos);
}
