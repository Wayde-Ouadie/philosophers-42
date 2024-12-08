#include "philo.h"

int	main(int ac, char **av)
{
	t_set	set;

	if (ac < 5 || ac > 6)
	{
		ft_fprintf(2, "Error: Incorrect number of arguments.\nUse example:\n");
		ft_fprintf(2, "./philo %s\n", ARGS_ERR);
		error("Last argument is optional.\n");
	}
	init_set(&set, ac, av);
	return (EXIT_SUCCESS);
}
