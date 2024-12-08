#include "philo.h"

void	printer(t_set *set, int id, char *msg)
{
	pthread_mutex_lock(&set->printing);
	if (!set->died)
		ft_fprintf(1, "%ld %d %s\n", calc_time() - set->start_time, id, msg);
	pthread_mutex_unlock(&set->printing);
}

void	error(char *err_msg)
{
	ft_fprintf(2, "%s\n", err_msg);
	exit(EXIT_FAILURE);
}

ssize_t	calc_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
