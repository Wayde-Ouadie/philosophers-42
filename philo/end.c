/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:01:10 by oel-feng@st       #+#    #+#             */
/*   Updated: 2024/12/20 23:55:33 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	calc_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_sleep(size_t time, t_set *set)
{
	size_t	i;

	i = calc_time();
	while (1)
	{
		pthread_mutex_lock(&set->death_check);
		if (calc_time() - i >= time || set->died == 1)
		{
			pthread_mutex_unlock(&set->death_check);
			break ;
		}
		pthread_mutex_unlock(&set->death_check);
		usleep(60);
	}
}

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
	pthread_mutex_destroy(&set->last_meal);
	pthread_mutex_destroy(&set->printing);
	pthread_mutex_destroy(&set->meal_check);
}

static void	check_death_helper(t_set *set, t_philo *philo, int i)
{
	pthread_mutex_lock(&set->last_meal);
	if (calc_time() - philo[i].last_meal_time > (size_t)set->death_time)
	{
		printer(set, philo[i].id, DEAD);
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
		pthread_mutex_lock(&set->meal_check);
		while (set->eat_requi != -1
			&& i < set->number && philo[i].eaten >= set->eat_requi)
			i++;
		pthread_mutex_unlock(&set->meal_check);
		if (i == set->number)
		{
			pthread_mutex_lock(&set->death_check);
			set->died = 1;
			pthread_mutex_unlock(&set->death_check);
			break ;
		}
	}
}
