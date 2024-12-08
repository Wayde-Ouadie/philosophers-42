/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:18:46 by oel-feng@st       #+#    #+#             */
/*   Updated: 2024/12/08 17:19:08 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_routine(t_set *set, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < set->number)
		pthread_join(philo[i].thread_id, NULL);
	i = 0;
	while (i < set->number)
	{
		pthread_mutex_destroy(&set->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&set->death_check);
}
