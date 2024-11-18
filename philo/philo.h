/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:42:23 by oel-feng          #+#    #+#             */
/*   Updated: 2024/11/18 08:18:43 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define MALL_ERR "Error: Malloc Failure"
# define ARGS_ERR "Number_of_philosophers time_to_die time_to_eat\
	 time_to_sleep [number_of_times_each_philosopher_must_eat]"

void	error(char *err_msg);
int		*tab_fill(int ac, char **av);
int		ft_fprintf(int fd, const char *format, ...);
void	error(char *err_msg);

#endif