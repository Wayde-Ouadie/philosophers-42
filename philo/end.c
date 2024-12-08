/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:01:10 by oel-feng@st       #+#    #+#             */
/*   Updated: 2024/12/08 18:43:11 by oel-feng@st      ###   ########.fr       */
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

static void	check_death_helper(t_set *set, t_philo *philo, int i)
{
	pthread_mutex_lock(&set->last_meal);
	if (calc_time() - philo[i].last_meal_time > set->death_time)
	{
		printer(set, philo[i].id, "died");
		pthread_mutex_lock(&set->death_check);
		set->died = 1;
		pthread_mutex_unlock(&set->death_check);
	}
	pthread_mutex_unlock(&set->last_meal);
}

void	check_death(t_set *set, t_philo *philo, int i)
{
	while (!set->died)
	{
		i = -1;
		while (++i < set->number && !set->died)
			check_death_helper(set, philo, i);
		if (set->died)
			break ;
		i = 0;
		while (set->eat_requi != -1
			&& i < set->number && philo[i].eaten >= set->eat_requi)
			i++;
		if (i == set->number)
		{
			pthread_mutex_lock(&set->death_check);
			set->died = 1;
			pthread_mutex_unlock(&set->death_check);
			break ;
		}
	}
}
