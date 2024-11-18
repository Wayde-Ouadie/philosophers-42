/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:42:17 by oel-feng          #+#    #+#             */
/*   Updated: 2024/11/18 08:42:00 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int	*tab;

	if (ac < 5 || ac > 6)
	{
		ft_fprintf(2, "Error: Incorrect number of arguments.\nUse example:\n");
		ft_fprintf(2, "./philo %s\n", ARGS_ERR);
		error("Last argument is optional.\n");
	}
	tab = tab_fill(ac, av);
	if (!tab)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
