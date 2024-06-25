/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgabovs <vgabovs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:04:06 by vgabovs           #+#    #+#             */
/*   Updated: 2024/06/25 21:06:20 by vgabovs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *arg)
{
	t_philo	*philo;
	t_prog	*prog;

	philo = (t_philo *)arg;
	prog = philo->prog;
	print_state(philo, THINK);
	print_state(philo, FORK);
	ft_usleep(prog->time_to_die, philo);
	print_state(philo, DEAD);
	return (NULL);
}

void	routine(t_philo *philo, t_prog *prog)
{
	int	status;

	status = 0;
	while (!stop_func(prog))
	{
		status = wait_for_forks(philo);
		if (!status && !stop_func(prog))
			status = philo_eat(philo, prog);
		if (!status && !stop_func(prog))
			status = philo_sleep(philo, prog);
		if (!status && !stop_func(prog))
			print_state(philo, THINK);
		if (status && !stop_func(prog))
		{
			print_state(philo, DEAD);
			break ;
		}
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_prog	*prog;

	philo = (t_philo *)arg;
	prog = philo->prog;
	print_state(philo, THINK);
	if (philo->id % 2 == 0)
		ft_usleep(prog->time_to_eat, philo);
	routine(philo, prog);
	return (NULL);
}

void	thread_start(t_philo *philo, t_prog *prog)
{
	int	i;

	i = 0;
	if (prog->num_of_philos == 1)
	{
		pthread_create(&prog->philos[i], NULL, &one_philo, &philo[i]);
		pthread_join(prog->philos[i], NULL);
		return ;
	}
	pthread_mutex_lock(&prog->print);
	while (i < prog->num_of_philos)
	{
		pthread_create(&prog->philos[i], NULL, &philo_routine, &philo[i]);
		i++;
	}
	pthread_mutex_unlock(&prog->print);
	i = 0;
	while (i < prog->num_of_philos)
	{
		pthread_join(prog->philos[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo	philo[MAX_PHILOS];
	t_prog	prog;

	if (program_check(argc, argv))
		return (1);
	if (init_prog(&prog, argc, argv))
		return (printf("Error: Program Initialization failed\n"), 1);
	if (init_philo(philo, &prog))
		return (printf("Error: Philo Initialization failed\n"), 1);
	thread_start(philo, &prog);
	free_all(&prog, philo);
	return (0);
}
