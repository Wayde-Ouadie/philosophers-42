/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:48:22 by oel-feng@st       #+#    #+#             */
/*   Updated: 2024/12/08 18:35:18 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *str, int check)
{
	int		i;

	if (str)
	{
		i = 0;
		while (str[i])
			i++;
		write(2, str, i);
	}
	if (check == 1)
		exit(EXIT_FAILURE);
}

void	printer(t_set *set, int id, char *msg)
{
	pthread_mutex_lock(&set->printing);
	if (!set->died)
		printf("%ld %d %s\n", calc_time() - set->start_time, id, msg);
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
		error("Error: Incorrect number of arguments.\n", 0);
		error("Use example:\n", 0);
		error("./philo ", 0);
		error(ARGS_ERR, 0);
		error("\nLast argument is optional.\n", 1);
	}
	init_set(&set, ac, av);
	init_routine(&set);
	return (EXIT_SUCCESS);
}
