/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:48:16 by oel-feng@st       #+#    #+#             */
/*   Updated: 2024/12/08 15:56:56 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end_routine(t_set *set, t_philo *philo)
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
	pthread_mutex_destroy(&set->printing);
}

static void	check_death(t_set *set, t_philo *philo, int i)
{
	while (!set->died)
	{
		i = -1;
		while (++i < set->number && !set->died)
		{
			pthread_mutex_lock(&set->check_eat_2);
			if (calc_time() - philo[i].last_meal_time > set->death_time)
			{
				printer(set, philo[i].id, "died");
				1 && (pthread_mutex_lock(&set->death_check), set->died = 1);
				pthread_mutex_unlock(&set->death_check);
			}
			pthread_mutex_unlock(&set->check_eat_2);
		}
		if (set->died)
			break ;
		i = 0;
		while (set->eat_requi != -1
			&& i < set->number && philo[i].eaten >= set->eat_requi)
			i++;
		if (i == set->number)
		{
			1 && (pthread_mutex_lock(&set->death_check), set->died = 1);
			pthread_mutex_unlock(&set->death_check);
			break ;
		}
	}
}

static void	eating_routine(t_philo *ph)
{
	t_set	*set;

	set = ph->set;
	pthread_mutex_lock(&set->forks[ph->l_fork]);
	printer(set, ph->id, "has taken a fork");
	pthread_mutex_lock(&set->forks[ph->r_fork]);
	printer(set, ph->id, "has taken a fork");
	pthread_mutex_lock(&set->check_eat_2);
	printer(set, ph->id, "is eating");
	ph->last_meal_time = calc_time();
	pthread_mutex_unlock(&set->check_eat_2);
	usleep(set->eat_time * 1000);
	ph->eaten++;
	pthread_mutex_unlock(&set->forks[ph->l_fork]);
	pthread_mutex_unlock(&set->forks[ph->r_fork]);
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
			error("Error: Thread creation failed.");
		philo[i].last_meal_time = calc_time();
	}
	check_death(set, philo, -1);
	end_routine(set, philo);
}
