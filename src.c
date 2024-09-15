/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaddou <hakaddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:21:47 by hakaddou          #+#    #+#             */
/*   Updated: 2023/01/08 16:53:43 by hakaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t n, size_t size)
{
	char		*tmp;

	if (n == INT_MAX && size == INT_MAX)
		return (NULL);
	tmp = malloc(n * size);
	if (tmp == NULL)
		return (tmp);
	ft_bzero(tmp, size * n);
	return (tmp);
}

int	ft_atoi(const char *str)
{
	unsigned long	sum;
	int				sign;

	sum = 0;
	sign = 1;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + *str - '0';
		str++;
	}
	if (sum > 2147483647 && sign == 1)
		return (-1);
	if (sum > 2147483648 && sign == -1)
		return (-1);
	if (sign == -1)
		return (-1);
	return (sum * sign);
}

/*	exists in struct_init.c and used to print philosophers information	*/

void	print_states(t_states *states)
{
	int	i;

	i = -1;
	while (++i < 200)
	{
		printf("philo %d left fork is %d and right fork is %d",
			states->philos[i].philo_id, states->philos[i].left_fork_id,
			states->philos[i].right_fork_id);
		if (states->philos[i].dead == true)
			printf(" and doesn't exist\n");
		else
			printf("\n");
	}
}
