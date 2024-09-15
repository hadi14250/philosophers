/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaddou <hakaddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:53:52 by hakaddou          #+#    #+#             */
/*   Updated: 2023/01/08 17:23:04 by hakaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <time.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_state	t_states;

# define NOT_TAKEN	-1
# define THINKING	1
# define EATING		2
# define SLEEPING	3
# define TWO_FORKS_TAKEN 4
# define TOOK_FORK	5
# define DIED		6

typedef struct s_philos
{
	pthread_t	thread;
	bool		dead;
	t_states	*states;
	int			left_fork_id;
	int			right_fork_id;
	int			pstate;
	int			philo_id;
	int			taken_fork[2];
	int			last_eaten;
	int			start_time;
	int			times_eaten;
	int			current_time;
}	t_philos;

typedef struct s_state
{
	t_philos		*philos;
	pthread_mutex_t	mutex[200];
	pthread_mutex_t	dead_check;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	print_died;
	pthread_mutex_t	all_eaten_mutex;
	pthread_mutex_t	time_mutex;
	int				fork[200];
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				current_time;
	int				times_must_eat;
	bool			someone_died;
	int				id_died;
	size_t			time_of_death;
	bool			should_exit;
	bool			all_eaten;
	bool			printed_died;
}	t_states;

/*	checks for errors	*/
void	error_check(int error);

int		num_check(t_states *states, int ac);

int		arg_check(int ac, char **av);

void	ft_usleep(size_t time);

size_t	current_time_fun(void);

size_t	time_passed(size_t current_time);

/*	struct initialization functions	*/
int		init_structs(int ac, char **av, t_states *states);

void	init_states_struct(int ac, char **av, t_states *states);

int		init_philos_structs(t_states *states);

void	init_unactive_structs(t_states *states);

void	print_states(t_states *states);

/*	initialises the threads	*/
int		init_philos(t_states *states);

void	*function(void *philos);

int		join_philos(t_states *states);

int		init_mutexes(t_states *states);

int		destroy_mutexes(t_states *states);

// state printing functions

void	print_thinking(t_philos *philo, size_t current_time);

void	print_took_fork(t_philos *philo, size_t current_time);

void	print_eating(t_philos *philo, size_t current_time);

void	print_sleeping(t_philos *philo, size_t current_time);

void	print_philo_died(t_philos *philo, size_t current_time);

/* srcs	*/

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t n, size_t size);

int		ft_atoi(const char *str);

void	print_states(t_states *states);

/*	simualtion	*/

int		check_starving(t_philos *philo, size_t current_time);

void	lock_in_order(t_philos *philo);

int		find_forks(t_philos *philo, size_t current_time);

bool	check_all_eaten(t_philos *philo);

void	print_and_fond_forks(t_philos *philo, size_t current_time);

void	print_state(t_philos *philo, size_t current_time, int state);

#endif