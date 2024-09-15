/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaddou <hakaddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:03:56 by hakaddou          #+#    #+#             */
/*   Updated: 2023/01/08 18:39:50 by hakaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_empty(int ac, char **av)
{
	int	i;
	int	d;

	i = 1;
	while (i < ac)
	{
		if (!av[i][0])
			return (printf("can't use empty arguments\n") * 0 -1);
		i++;
	}
	i = 0;
	while (++i < ac)
	{
		d = -1;
		while (av[i][++d] != '\0')
		{
			if (av[i][d] == ' ')
			{
				printf("Do not use spaces\n");
				return (-1);
			}
		}
	}
	return (0);
}

int	check_alphas(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if ((av[i][j] < '0' && (av[i][j] != ' ' && av[i][j] != '-'
			&& av[i][j] != '+'))
			|| (av[i][j] > '9' && (av[i][j] != ' ' && av[i][j] != '-'
			&& av[i][j] != '+')))
			{
				printf("Only use numbers\n");
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	neg_check(int ac, char **av)
{
	int	i;
	int	d;

	i = 1;
	while (i < ac)
	{
		d = 0;
		while (av[i][d] != '\0')
		{
			if ((av[i][d] == '-' && (av[i][d + 1] < '0' || av[i][d + 1] > '9'))
			|| (av[i][d] == '+' && (av[i][d + 1] < '0' || av[i][d + 1] > '9')))
			{
				printf("Numbers only\n");
				return (-1);
			}
			d++;
		}
		i++;
	}
	return (0);
}

int	arg_check(int ac, char **av)
{
	int	num_philos;

	if (ac < 5 || ac > 6)
	{
		printf("Include correct num of args\n");
		return (-1);
	}
	num_philos = atoi(av[1]);
	if (num_philos < 1)
	{
		printf("Should be atleast one philo\n");
		return (-1);
	}
	else if (num_philos > 200)
	{
		printf("Should be less than or equal to 200 philos\n");
		return (-1);
	}
	if (check_empty(ac, av) == -1)
		return (-1);
	if (check_alphas(ac, av) == -1)
		return (-1);
	if (neg_check(ac, av) == -1)
		return (-1);
	return (0);
}

int	num_check(t_states *states, int ac)
{
	if (states->num_philos == -1 || states->time_to_die == -1
		|| states->time_to_eat == -1 || states->time_to_sleep == -1)
	{
		printf("numbers can only be postive and within MAX_INT limt\n");
		return (-1);
	}
	if (states->time_to_eat < 60 || states->time_to_sleep < 60)
	{
		printf("You can only use 60+ ms for sleeping and eating times\n");
		return (-1);
	}
	if (ac == 6)
		if (states->times_must_eat == -1)
			return (-1);
	return (0);
}
