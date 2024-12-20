/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:48:19 by oel-feng@st       #+#    #+#             */
/*   Updated: 2024/12/10 22:55:10 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define EATING "is eating"
# define SLEEP "is sleeping"
# define THINKING "is thinking"
# define FORK "has taken a fork"

# define MALL_ERR "Error: Malloc Failure."
# define MUTEX_ERR "Error: Mutex init failed."
# define THREAD_ERR "Error: Thread creation failed."
# define ZERO_ERR "Error: Inputs can't be equal to 0."
# define INVALID_NBR "Error: Input valid number."
# define INVALID_PHILO "Error: Invalid number of philo."
# define NO_SIGNS "Error: Input only positive number without sign."
# define MAX_INPUT "Error: Input number smaller or equal to int max."
# define INVALID_INPUT "Error: time_to_die or time_to_eat or time_to_sleep\
set to values lower than 60."
# define ARGS_ERR_1 "Error: Incorrect number of arguments.\nUse example:\n./\
philo Number_of_philosophers time_to_die time_to_eat" 
# define ARGS_ERR_2 " time_to_sleep [number_of_times_each_philosopher_must_eat].\
\nLast argument is optional.\n"

typedef struct s_philo
{
	int				id;
	int				eaten;
	int				l_fork;
	int				r_fork;
	size_t			last_meal_time;
	pthread_t		thread_id;
	struct s_set	*set;
}	t_philo;

typedef struct s_set
{
	int				number;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				eat_requi;
	int				died;
	size_t			check_eat_1;
	size_t			start_time;
	pthread_mutex_t	death_check;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	printing;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	forks[200];
	t_philo			philo[200];
}	t_set;

size_t	calc_time(void);
void	error(char *str);
int		init_routine(t_set *set);
void	my_sleep(size_t time, t_set *set);
void	printer(t_set *set, int id, char *msg);
int		init_set(t_set *set, int ac, char **av);
void	end_routine(t_set *set, t_philo *philo);
void	check_death(t_set *set, t_philo *philo, int i);

#endif