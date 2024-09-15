/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaddou <hakaddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 05:08:12 by hakaddou          #+#    #+#             */
/*   Updated: 2023/01/08 18:37:48 by hakaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*function(void *philos)
{
	t_philos	*philo;
	size_t		current_time;

	philo = (t_philos *) philos;
	current_time = current_time_fun();
	while (1)
	{
		if (check_all_eaten(philo) == true)
			break ;
		if (check_starving(philo, current_time) == -1)
			break ;
		if (philo->pstate == THINKING)
			print_and_fond_forks(philo, current_time);
		if (philo->pstate == EATING)
			philo->pstate = SLEEPING;
		if (philo->pstate == SLEEPING)
		{
			print_state(philo, current_time, SLEEPING);
			ft_usleep(philo->states->time_to_sleep);
			philo->pstate = THINKING;
		}
		usleep(100);
	}
	return (philo);
}

void	print_state(t_philos *philo, size_t current_time, int state)
{
	pthread_mutex_lock(&philo->states->print_died);
	if (state == THINKING && philo->states->printed_died == false)
		print_thinking(philo, current_time);
	else if (state == TOOK_FORK && philo->states->printed_died == false)
		print_took_fork(philo, current_time);
	else if (state == EATING && philo->states->printed_died == false)
		print_eating(philo, current_time);
	else if (state == SLEEPING && philo->states->printed_died == false)
		print_sleeping(philo, current_time);
	else if (state == DIED && philo->dead == true
		&& philo->states->printed_died == false)
		print_philo_died(philo, current_time);
	pthread_mutex_unlock(&philo->states->print_died);
}

int	init_philos(t_states *states)
{
	int	error;
	int	i;

	i = -1;
	error = 0;
	while (++i < states->num_philos)
	{
		error = pthread_create(&states->philos[i].thread, NULL,
				&function, &states->philos[i]);
		if (error != 0)
		{
			printf("error while creating thread %d\n", i + 1);
			return (1);
		}
		usleep(100);
	}
	return (0);
}

/*	waits for all threads to finish execution	*/
int	join_philos(t_states *states)
{
	int	error;
	int	i;

	i = -1;
	error = 0;
	while (++i < states->num_philos)
	{
		error = pthread_join(states->philos[i].thread, NULL);
		if (error != 0)
		{
			printf("error while joining thread %d\n", i + 1);
			return (1);
		}
	}
	return (0);
}
