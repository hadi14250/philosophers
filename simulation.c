/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaddou <hakaddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:28:24 by hakaddou          #+#    #+#             */
/*   Updated: 2023/01/08 18:37:44 by hakaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_starving(t_philos *philo, size_t current_time)
{
	int	time_p;

	pthread_mutex_lock(&philo->states->dead_check);
	time_p = time_passed(current_time);
	if (time_p >= philo->last_eaten + philo->states->time_to_die)
	{
		philo->dead = true;
		philo->states->someone_died = true;
		philo->states->should_exit = true;
		philo->states->id_died = philo->philo_id;
		philo->states->time_of_death = time_passed(current_time);
		print_state(philo, current_time, DIED);
	}
	if (philo->states->someone_died == true)
	{
		pthread_mutex_unlock(&philo->states->dead_check);
		return (-1);
	}
	pthread_mutex_unlock(&philo->states->dead_check);
	return (0);
}

void	lock_in_order(t_philos *philo)
{
	if (philo->left_fork_id < philo->right_fork_id)
	{
		pthread_mutex_lock(&philo->states->mutex[philo->left_fork_id]);
		pthread_mutex_lock(&philo->states->mutex[philo->right_fork_id]);
	}
	else
	{
		pthread_mutex_lock(&philo->states->mutex[philo->right_fork_id]);
		pthread_mutex_lock(&philo->states->mutex[philo->left_fork_id]);
	}
}

int	find_forks(t_philos *philo, size_t current_time)
{
	if (check_starving(philo, current_time) == -1)
		return (-1);
	print_state(philo, current_time, DIED);
	lock_in_order(philo);
	if (philo->states->num_philos % 2 == 0
		&& check_starving(philo, current_time) == -1)
	{
		pthread_mutex_unlock(&philo->states->mutex[philo->left_fork_id]);
		pthread_mutex_unlock(&philo->states->mutex[philo->right_fork_id]);
		return (-1);
	}
	philo->states->fork[philo->left_fork_id] = philo->philo_id;
	philo->states->fork[philo->right_fork_id] = philo->philo_id;
	print_state(philo, current_time, TOOK_FORK);
	print_state(philo, current_time, TOOK_FORK);
	print_state(philo, current_time, EATING);
	philo->pstate = EATING;
	philo->last_eaten = time_passed(current_time);
	ft_usleep(philo->states->time_to_eat);
	pthread_mutex_lock(&philo->states->all_eaten_mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->states->all_eaten_mutex);
	pthread_mutex_unlock(&philo->states->mutex[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->states->mutex[philo->right_fork_id]);
	return (0);
}

/*	
if (philo->states->fork[philo->left_fork_id] == philo->philo_id
	&& philo->states->fork[philo->right_fork_id] == philo->philo_id)
{
}
*/

bool	check_all_eaten(t_philos *philo)
{
	int	i;
	int	d;

	pthread_mutex_lock(&philo->states->all_eaten_mutex);
	if (philo->states->times_must_eat == -1)
	{
		pthread_mutex_unlock(&philo->states->all_eaten_mutex);
		return (false);
	}
	i = -1;
	d = 0;
	while (++i < philo->states->num_philos)
	{
		if (philo->times_eaten >= philo->states->times_must_eat)
			d++;
	}
	if (d == philo->states->num_philos)
	{
		philo->states->all_eaten = true;
		pthread_mutex_unlock(&philo->states->all_eaten_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->states->all_eaten_mutex);
	return (false);
}

void	print_and_fond_forks(t_philos *philo, size_t current_time)
{
	print_state(philo, current_time, THINKING);
	find_forks(philo, current_time);
}
