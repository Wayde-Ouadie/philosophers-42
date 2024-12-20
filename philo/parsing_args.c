/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:48:25 by oel-feng@st       #+#    #+#             */
/*   Updated: 2024/12/10 22:58:12 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parsing(char **str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++j])
	{
		i = -1;
		while (str[j][++i])
		{
			if (i == 0 && (str[j][i] == '+' || str[j][i] == '-'))
				return (error(NO_SIGNS), -1);
			else if (!(str[j][i] >= '0' && str[j][i] <= '9'))
				return (error(INVALID_INPUT), -1);
		}
	}
	return (1);
}

static int	ft_atoi(char *str)
{
	int	i;
	int	tmp;
	int	result;

	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = result * 10 - (48 - str[i++]);
		if (tmp < result)
			return (-1337);
		result = tmp;
	}
	return (result);
}

static void	init_philo(t_set *set)
{
	int	i;

	i = set->number;
	while (--i >= 0)
	{
		set->philo[i].id = i + 1;
		set->philo[i].eaten = 0;
		set->philo[i].last_meal_time = 0;
		set->philo[i].set = set;
		set->philo[i].l_fork = i;
		set->philo[i].r_fork = (i + 1) % set->number;
	}
}

static int	init_mutex(t_set *set)
{
	int	i;

	i = set->number;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(set->forks[i]), NULL))
			return (error(MUTEX_ERR), -1);
	}
	if (pthread_mutex_init(&set->last_meal, NULL))
		return (error(MUTEX_ERR), -1);
	if (pthread_mutex_init(&set->death_check, NULL))
		return (error(MUTEX_ERR), -1);
	if (pthread_mutex_init(&set->printing, NULL))
		return (error(MUTEX_ERR), -1);
	if (pthread_mutex_init(&set->meal_check, NULL))
		return (error(MUTEX_ERR), -1);
	return (1);
}

int	init_set(t_set *set, int ac, char **av)
{
	if (parsing(av) == -1)
		return (-1);
	set->number = ft_atoi(av[1]);
	if (set->number > 200)
		return (error(INVALID_PHILO), -1);
	set->death_time = ft_atoi(av[2]);
	set->eat_time = ft_atoi(av[3]);
	set->sleep_time = ft_atoi(av[4]);
	1 && (set->died = 0, set->check_eat_1 = 0);
	if (ac == 6)
		set->eat_requi = ft_atoi(av[5]);
	else
		set->eat_requi = -1;
	if (set->number == -1337 || set->death_time == -1337
		|| set->eat_time == -1337 || set->sleep_time == -1337
		|| set->eat_requi == -1337)
		return (error(MAX_INPUT), -1);
	if (set->number == 0 || set->eat_requi == 0)
		return (error(ZERO_ERR), -1);
	if (set->death_time < 60 || set->eat_time < 60 || set->sleep_time < 60)
		return (error(INVALID_INPUT), -1);
	if (init_mutex(set) == -1)
		return (-1);
	init_philo(set);
	return (1);
}
