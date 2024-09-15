/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaddou <hakaddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:33:06 by hakaddou          #+#    #+#             */
/*   Updated: 2023/01/08 15:34:53 by hakaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_thinking(t_philos *philo, size_t current_time)
{
	pthread_mutex_lock(&philo->states->print_mutex);
	printf("[%zu ms] \033[34mphilo %d is thinking\033[0m\n",
		time_passed(current_time), philo->philo_id);
	pthread_mutex_unlock(&philo->states->print_mutex);
}

void	print_took_fork(t_philos *philo, size_t current_time)
{
	pthread_mutex_lock(&philo->states->print_mutex);
	printf("[%zu ms] \033[33mphilo %d took a fork\033[0m\n",
		time_passed(current_time), philo->philo_id);
	pthread_mutex_unlock(&philo->states->print_mutex);
}

void	print_eating(t_philos *philo, size_t current_time)
{
	pthread_mutex_lock(&philo->states->print_mutex);
	printf("[%zu ms] \033[32mphilo %d is eating\033[0m\n",
		time_passed(current_time), philo->philo_id);
	pthread_mutex_unlock(&philo->states->print_mutex);
}

void	print_sleeping(t_philos *philo, size_t current_time)
{
	pthread_mutex_lock(&philo->states->print_mutex);
	printf("[%zu ms] \033[35mphilo %d is sleeping\033[0m\n",
		time_passed(current_time), philo->philo_id);
	pthread_mutex_unlock(&philo->states->print_mutex);
}

void	print_philo_died(t_philos *philo, size_t current_time)
{
	pthread_mutex_lock(&philo->states->print_mutex);
	philo->states->printed_died = true;
	printf("[%zu ms] \033[31mphilo %d has died\033[0m\n",
		time_passed(current_time), philo->philo_id);
	pthread_mutex_unlock(&philo->states->print_mutex);
}
