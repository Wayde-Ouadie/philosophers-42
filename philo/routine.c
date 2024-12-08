/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:48:16 by oel-feng@st       #+#    #+#             */
/*   Updated: 2024/12/08 18:33:43 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating_routine(t_philo *ph)
{
	t_set	*set;

	set = ph->set;
	if (set->number == 1)
	{
		printer(set, ph->id, "has taken a fork");
		usleep(set->death_time);
	}
	else
	{
		pthread_mutex_lock(&set->forks[ph->l_fork]);
		printer(set, ph->id, "has taken a fork");
		pthread_mutex_lock(&set->forks[ph->r_fork]);
		printer(set, ph->id, "has taken a fork");
		pthread_mutex_lock(&set->last_meal);
		printer(set, ph->id, "is eating");
		ph->last_meal_time = calc_time();
		pthread_mutex_unlock(&set->last_meal);
		usleep(set->eat_time * 1000);
		ph->eaten++;
		pthread_mutex_unlock(&set->forks[ph->l_fork]);
		pthread_mutex_unlock(&set->forks[ph->r_fork]);
	}
}

static void	*routine(void *philo)
{
	int		i;
	t_philo	*ph;
	t_set	*set;

	ph = (t_philo *)philo;
	1 && (set = ph->set, i = 0);
	if (ph->id % 2)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&set->death_check);
		if (set->died)
		{
			pthread_mutex_unlock(&set->death_check);
			break ;
		}
		pthread_mutex_unlock(&set->death_check);
		eating_routine(ph);
		printer(set, ph->id, "is sleeping");
		usleep(set->sleep_time * 1000);
		printer(set, ph->id, "is thinking");
		if (set->eat_requi && ++i == set->eat_requi)
			break ;
	}
	return (NULL);
}

void	init_routine(t_set *set)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = set->philo;
	set->start_time = calc_time();
	while (++i < set->number)
	{
		if (pthread_create(&philo[i].thread_id, NULL, routine, &philo[i]))
			error("Error: Thread creation failed.", 1);
		philo[i].last_meal_time = calc_time();
	}
	check_death(set, philo, -1);
	end_routine(set, philo);
}
