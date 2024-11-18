/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 04:49:04 by oel-feng          #+#    #+#             */
/*   Updated: 2024/11/18 08:27:39 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(char *str)
{
	int		i;
	long	tmp;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = result * 10 - (48 - str[i++]);
		if (tmp < result)
			error("Error: Input valid number");
		result = tmp;
	}
	return ((int)result);
}

int	*tab_fill(int ac, char **av)
{
	int	i;
	int	*tab;

	1 && (i = 0, tab = malloc(sizeof(int) * ac));
	if (!tab)
		return (ft_fprintf(2, "%s\n", MALL_ERR), NULL);
	while (++i < ac)
		tab[i - 1] = ft_atoi(av[i]);
	tab[i - 1] = '\0';
	return (tab);
}
