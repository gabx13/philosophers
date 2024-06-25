/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgabovs <vgabovs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:00:30 by vgabovs           #+#    #+#             */
/*   Updated: 2024/06/25 21:04:52 by vgabovs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define MAX_PHILOS 200

typedef struct s_prog		t_prog;
typedef struct s_philo		t_philo;
typedef enum print_state	t_print_state;
typedef struct s_fork		t_fork;

typedef enum print_state
{
	DEAD,
	FORK,
	EAT,
	SLEEP,
	THINK
}	t_print_state;

struct s_philo
{
	int					id;
	int					times_ate;
	long				last_eat;
	t_prog				*prog;
	t_fork				*l_fork;
	t_fork				*r_fork;
};

struct s_prog
{
	int					num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_meals;
	int					dead;
	int					full_philos;
	long				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_t			*philos;
};

struct s_fork
{
	int					taken;
	pthread_mutex_t		*fork;
};

int			init_philo(t_philo *philo, t_prog *prog);
int			init_prog(t_prog *prog, int argc, char **argv);

size_t		get_current_time(void);
int			ft_usleep(int time, t_philo *philo);
int			ft_atoi(const char *str);
void		print_state(t_philo *philo, t_print_state state);
size_t		ft_strlen(const char *s);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
int			check_dead(t_philo *philo);
int			stop_func(t_prog *prog);
int			program_check(int argc, char **argv);
void		*philo_routine(void *arg);
int			wait_for_forks(t_philo *philo);
int			put_fork(t_philo *philo, t_fork *fork);
int			take_fork(t_philo *philo, t_fork *fork);
int			philo_eat(t_philo *philo, t_prog *prog);
int			philo_sleep(t_philo *philo, t_prog *prog);
void		*one_philo(void *arg);
void		free_all(t_prog *prog, t_philo *philo);
#endif
