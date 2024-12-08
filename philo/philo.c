/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:48:22 by oel-feng@st       #+#    #+#             */
/*   Updated: 2024/12/08 17:18:38 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	error_print(char *str)
{
	int		i;
	size_t	size;

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
	pthread_mutex_lock(&set->death_check);
	if (!set->died)
		printf("%ld %d %s\n", calc_time() - set->start_time, id, msg);
	pthread_mutex_unlock(&set->death_check);
}

void	error(char *err_msg)
{
	error_print(err_msg);
	exit(EXIT_FAILURE);
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
		error_print("Error: Incorrect number of arguments.\nUse example:\n");
		error_print("./philo ");
		error_print(ARGS_ERR);
		error("\nLast argument is optional.\n");
	}
	init_set(&set, ac, av);
	init_routine(&set);
	return (EXIT_SUCCESS);
}
