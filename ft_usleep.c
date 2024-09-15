/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaddou <hakaddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:26:01 by hakaddou          #+#    #+#             */
/*   Updated: 2023/01/08 15:17:20 by hakaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

size_t	current_time_fun(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

/*	it delays the execution of a thread by the
	specified millisceconds as argument.
	this does not use the usleep function whihch makes
	it more accurate to the exact milllisecond.	*/
void	ft_usleep(size_t time)
{
	size_t	end;

	end = current_time_fun() + time;
	while (current_time_fun() < end)
		usleep(time);
}

size_t	time_passed(size_t current_time)
{
	return (current_time_fun() - current_time);
}
