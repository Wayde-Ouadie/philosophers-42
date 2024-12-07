/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:42:23 by oel-feng          #+#    #+#             */
/*   Updated: 2024/12/07 09:52:55 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define MALL_ERR "Error: Malloc Failure."
# define ARGS_ERR "Number_of_philosophers time_to_die time_to_eat\
	 time_to_sleep [number_of_times_each_philosopher_must_eat]."
# define INVALID_INPUT "Error: time_to_die or time_to_eat or time_to_sleep\
	 set to values lower than 60."

typedef struct s_set
{
	size_t			number;
	size_t			death_time;
	size_t			eat_time;
	size_t			sleep_time;
	long			eat_requi;
	int				died;
	size_t			check_eat_1;
	size_t			start_time;
	pthread_mutex_t	check_eat_2;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printing;
	struct s_philo	*philo;
}	t_set;

typedef struct s_philo
{
	int			id;
	int			eaten;
	int			l_fork;
	int			r_fork;
	size_t		last_meal_time;
	pthread_t	thread_id;
	t_set		*set;
}	t_philo;

void	parsing(char **str);
void	error(char *err_msg);
void	init_set(t_set *set, int ac, char **av);
int		ft_fprintf(int fd, const char *format, ...);

#endif