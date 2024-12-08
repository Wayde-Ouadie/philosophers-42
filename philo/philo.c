/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:48:22 by oel-feng@st       #+#    #+#             */
/*   Updated: 2024/12/08 14:48:23 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_set	set;

	if (ac < 5 || ac > 6)
	{
		ft_fprintf(2, "Error: Incorrect number of arguments.\nUse example:\n");
		ft_fprintf(2, "./philo %s\n", ARGS_ERR);
		error("Last argument is optional.\n");
	}
	init_set(&set, ac, av);
	init_routine(&set);
	return (EXIT_SUCCESS);
}
