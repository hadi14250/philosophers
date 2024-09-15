/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaddou <hakaddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:04:03 by hakaddou          #+#    #+#             */
/*   Updated: 2023/01/08 17:23:32 by hakaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_structs(int ac, char **av, t_states *states)
{
	states->philos = ft_calloc(sizeof(t_philos), 200);
	if (states->philos == NULL)
		return (-1);
	init_states_struct(ac, av, states);
	if (num_check(states, ac) == -1)
	{
		free (states->philos);
		return (-1);
	}
	if (init_philos_structs(states) == -1)
		return (-1);
	init_unactive_structs(states);
	return (0);
}

void	init_states_struct(int ac, char **av, t_states *states)
{
	int	i;

	i = -1;
	states->num_philos = ft_atoi(av[1]);
	states->time_to_die = ft_atoi(av[2]);
	states->time_to_eat = ft_atoi(av[3]);
	states->time_to_sleep = ft_atoi(av[4]);
	states->current_time = current_time_fun();
	states->someone_died = false;
	states->all_eaten = false;
	states->printed_died = false;
	states->should_exit = false;
	if (ac == 6)
		states->times_must_eat = ft_atoi(av[5]);
	else
		states->times_must_eat = -1;
	while (++i < 200)
		states->fork[i] = NOT_TAKEN;
}

void	check_time_to_eat(t_states *states)
{
	size_t	current_time;

	current_time = current_time_fun();
	if (states->num_philos == 1)
	{
		printf("[%zu ms] \033[34mphilo 1 is thinking\033[0m\n",
			time_passed(current_time));
		printf("[%zu ms] \033[33mphilo 1 took a fork\033[0m\n",
			time_passed(current_time));
		ft_usleep(states->time_to_die);
	}
	else
	{
		printf("[%zu ms] \033[34mphilo 1 is thinking\033[0m\n",
			time_passed(current_time));
		printf("[%zu ms] \033[33mphilo 1 took a fork\033[0m\n",
			time_passed(current_time));
		printf("[%zu ms] \033[33mphilo 1 took a fork\033[0m\n",
			time_passed(current_time));
		ft_usleep(states->time_to_die);
	}
	printf("[%d ms] \033[31mphilo 1 died\033[0m\n", states->time_to_die);
	free(states->philos);
}

int	init_philos_structs(t_states *states)
{
	int	i;

	i = -1;
	while (++i < states->num_philos)
	{
		states->philos[i].states = states;
		states->philos[i].philo_id = i + 1;
		states->philos[i].times_eaten = 0;
		states->philos[i].dead = false;
		states->philos[i].pstate = THINKING;
	}
	i = -1;
	while (++i < states->num_philos - 1)
	{
		states->philos[i].left_fork_id = i;
		states->philos[i].right_fork_id = i + 1;
	}
	states->philos[i].left_fork_id = states->num_philos - 1;
	states->philos[i].right_fork_id = 0;
	if (states->num_philos == 1 || states->time_to_die <= states->time_to_eat)
	{
		check_time_to_eat(states);
		return (-1);
	}
	return (0);
}

/*	since there is 200 stack allocated structs
and if the philos are less than 200, this sets the unused
structs to their apprioprate values to avoid misuse*/
void	init_unactive_structs(t_states *states)
{
	int	i;

	i = 0;
	while (states->num_philos + i < 200)
	{
		states->philos[states->num_philos + i].left_fork_id = -2;
		states->philos[states->num_philos + i].right_fork_id = -2;
		states->philos[states->num_philos + i].taken_fork[0] = -2;
		states->philos[states->num_philos + i].taken_fork[1] = -2;
		states->fork[states->num_philos + i] = -2;
		states->philos[states->num_philos + i].pstate = -2;
		states->philos[states->num_philos + i].philo_id = -2;
		states->philos[states->num_philos + i].dead = true;
		i++;
	}
}
