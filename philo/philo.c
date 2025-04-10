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
