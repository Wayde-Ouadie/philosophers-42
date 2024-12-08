#include "philo.h"

void	error(char *err_msg)
{
	ft_fprintf(2, "%s\n", err_msg);
	exit(EXIT_FAILURE);
}
