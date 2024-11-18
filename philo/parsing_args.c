/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng@student.42.fr <oel-feng>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 04:49:04 by oel-feng          #+#    #+#             */
/*   Updated: 2024/11/18 08:41:46 by oel-feng@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parsing(char **str)
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
				error("Error: Input number without sign.");
			else if (!(str[j][i] >= '0' && str[j][i] <= '9'))
				error("Error: Input valid number.");
		}
	}
}

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
			error("Error: Input bigger than int max.");
		result = tmp;
	}
	return ((int)result);
}

int	*tab_fill(int ac, char **av)
{
	int	i;
	int	*tab;

	parsing(av);
	1 && (i = 0, tab = malloc(sizeof(int) * ac));
	if (!tab)
		return (ft_fprintf(2, "%s\n", MALL_ERR), NULL);
	while (++i < ac)
		tab[i - 1] = ft_atoi(av[i]);
	tab[i - 1] = '\0';
	return (tab);
}
