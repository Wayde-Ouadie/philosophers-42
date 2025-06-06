/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:48:16 by oel-feng@st       #+#    #+#             */
/*   Updated: 2024/12/10 22:55:05 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_check(t_philo *ph)
{
	t_set	*set;

	set = ph->set;
	pthread_mutex_lock(&set->printing);
	pthread_mutex_lock(&set->death_check);
	if (!set->died)
		printf("0 %d %s\n", ph->id, FORK);
	pthread_mutex_unlock(&set->death_check);
	pthread_mutex_unlock(&set->printing);
	my_sleep(set->death_time, set);
	printer(set, ph->id, DEAD);
}

static void	eating_routine(t_philo *ph)
{
	t_set	*set;

	set = ph->set;
	if (set->number == 1)
		return (philo_check(ph));
	else
	{
		pthread_mutex_lock(&set->forks[ph->l_fork]);
		printer(set, ph->id, FORK);
		pthread_mutex_lock(&set->forks[ph->r_fork]);
		printer(set, ph->id, FORK);
		pthread_mutex_lock(&set->last_meal);
		printer(set, ph->id, EATING);
		ph->last_meal_time = calc_time();
		pthread_mutex_unlock(&set->last_meal);
		my_sleep(set->eat_time, set);
		pthread_mutex_lock(&set->meal_check);
		ph->eaten++;
		pthread_mutex_unlock(&set->meal_check);
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
		my_sleep(set->eat_time, set);
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
		printer(set, ph->id, SLEEP);
		my_sleep(set->sleep_time, set);
		printer(set, ph->id, THINKING);
		if (set->eat_requi && ++i == set->eat_requi)
			break ;
	}
	return (NULL);
}

int	init_routine(t_set *set)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = set->philo;
	set->start_time = calc_time();
	while (++i < set->number)
	{
		if (pthread_create(&philo[i].thread_id, NULL, routine, &philo[i]))
			return (error(THREAD_ERR), -1);
		pthread_mutex_lock(&set->last_meal);
		philo[i].last_meal_time = calc_time();
		pthread_mutex_unlock(&set->last_meal);
	}
	check_death(set, philo, -1);
	end_routine(set, philo);
	return (1);
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
