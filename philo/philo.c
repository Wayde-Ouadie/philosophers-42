/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:48:22 by oel-feng@st       #+#    #+#             */
/*   Updated: 2024/12/10 22:49:16 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *str)
{
	int		i;

	if (str)
	{
		i = 0;
		while (str[i])
			i++;
		write(2, str, i);
	}
}

void	printer(t_set *set, int id, char *msg)
{
	pthread_mutex_lock(&set->printing);
	pthread_mutex_lock(&set->death_check);
	if (!set->died)
		printf("%ld %d %s\n", calc_time() - set->start_time, id, msg);
	pthread_mutex_unlock(&set->death_check);
	pthread_mutex_unlock(&set->printing);
}

size_t	calc_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	main(int ac, char **av)
{
	t_set	set;

	if (ac < 5 || ac > 6)
	{
		error(ARGS_ERR_1);
		error(ARGS_ERR_2);
		return (1);
	}
	if (init_set(&set, ac, av) == -1)
		return (1);
	if (init_routine(&set) == -1)
		return (1);
	return (0);
}
