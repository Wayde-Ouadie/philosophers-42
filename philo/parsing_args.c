/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:48:25 by oel-feng@st       #+#    #+#             */
/*   Updated: 2024/12/08 17:00:25 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	parsing(char **str)
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
				error("Error: Input only positive number without sign.");
			else if (!(str[j][i] >= '0' && str[j][i] <= '9'))
				error("Error: Input valid number.");
		}
	}
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
			error("Error: Input number smaller or equal to int max.");
		result = tmp;
	}
	if (result == 0)
		error("Error: Inputs can't equal 0.");
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

static void	init_set_2(t_set *set)
{
	int	i;

	i = set->number;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(set->forks[i]), NULL))
			error("Error: Mutex init failed.");
	}
	if (pthread_mutex_init(&set->printing, NULL))
		error("Error: Mutex init failed.");
	if (pthread_mutex_init(&set->check_eat_2, NULL))
		error("Error: Mutex init failed.");
	if (pthread_mutex_init(&set->death_check, NULL))
		error("Error: Mutex init failed.");
}

void	init_set(t_set *set, int ac, char **av)
{
	parsing(av);
	set->number = ft_atoi(av[1]);
	if (set->number > 200)
		error("Error: Invalid number of philo.");
	set->death_time = ft_atoi(av[2]);
	set->eat_time = ft_atoi(av[3]);
	set->sleep_time = ft_atoi(av[4]);
	if (set->death_time < 60 || set->eat_time < 60 || set->sleep_time < 60)
		error(INVALID_INPUT);
	set->died = 0;
	set->check_eat_1 = 0;
	if (ac == 6)
		set->eat_requi = ft_atoi(av[5]);
	else
		set->eat_requi = -1;
	init_set_2(set);
	init_philo(set);
}
