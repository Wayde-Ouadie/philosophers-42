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
	if (result = 0)
		error("Error: Inputs can't equal 0.");
	return (result);
}

void	init_set(t_set *set, int ac, char **av)
{
	int	i;

	parsing(av);
	i = 0;
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
}
