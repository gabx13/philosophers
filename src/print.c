/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgabovs <vgabovs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:11:20 by vgabovs           #+#    #+#             */
/*   Updated: 2024/06/25 21:06:57 by vgabovs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(char *str, long start_time, int id)
{
	ft_putnbr_fd((int)((get_current_time() - start_time)), 1);
	write(1, " ", 1);
	ft_putnbr_fd(id, 1);
	write(1, " ", 1);
	ft_putstr_fd(str, 1);
	write(1, "\n", 1);
}

void	print_state(t_philo *philo, t_print_state state)
{
	t_prog	*prog;

	prog = philo->prog;
	pthread_mutex_lock(&prog->print);
	if (prog->dead)
	{
		pthread_mutex_unlock(&prog->print);
		return ;
	}
	if (state == DEAD)
		ft_print("died", prog->start_time, philo->id);
	else if (state == FORK)
		ft_print("has taken a fork", prog->start_time, philo->id);
	else if (state == EAT)
		ft_print("is eating", prog->start_time, philo->id);
	else if (state == SLEEP)
		ft_print("is sleeping", prog->start_time, philo->id);
	else if (state == THINK)
		ft_print("is thinking", prog->start_time, philo->id);
	pthread_mutex_unlock(&prog->print);
}
