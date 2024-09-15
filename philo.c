/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaddou <hakaddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:04:00 by hakaddou          #+#    #+#             */
/*   Updated: 2023/01/08 17:59:18 by hakaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_states *states)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while (++i < states->num_philos)
	{
		error = pthread_mutex_init(&states->mutex[i], NULL);
		if (error != 0)
		{
			printf("error while initialsing mutex %d\n", i + 1);
			return (1);
		}
	}
	error = pthread_mutex_init(&states->dead_check, NULL);
	error = pthread_mutex_init(&states->print_mutex, NULL);
	error = pthread_mutex_init(&states->print_died, NULL);
	error = pthread_mutex_init(&states->all_eaten_mutex, NULL);
	if (error != 0)
	{
		printf("error while initialsing mutex\n");
		return (1);
	}
	return (0);
}

int	destroy_mutexes(t_states *states)
{
	int	i;
	int	error;

	error = 0;
	i = -1;
	while (++i < states->num_philos)
	{
		error = pthread_mutex_destroy(&states->mutex[i]);
		if (error != 0)
		{
			printf("error while destroying mutex %d\n", i + 1);
			return (1);
		}
	}
	error = pthread_mutex_destroy(&states->dead_check);
	error = pthread_mutex_destroy(&states->print_mutex);
	error = pthread_mutex_destroy(&states->print_died);
	error = pthread_mutex_destroy(&states->all_eaten_mutex);
	if (error != 0)
	{
		printf("error while destroying mutex\n");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_states	states;

	if (arg_check(ac, av) == -1)
		return (1);
	if (init_structs(ac, av, &states) == -1)
		return (1);
	if (init_mutexes(&states) == 1)
		return (1);
	if (init_philos(&states) == 1)
		return (1);
	if (join_philos(&states) == 1)
		return (1);
	if (states.all_eaten == true && states.someone_died == false)
		printf("\033[92mall philos eaten atleast %d times\033[0m\n",
			states.times_must_eat);
	if (destroy_mutexes(&states) == 1)
		return (1);
	free(states.philos);
}
