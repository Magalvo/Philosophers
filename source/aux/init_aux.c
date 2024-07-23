#include "../../include/philosophers.h"

//100 ou mais;
int	ft_usleep(size_t time)
{
	long long	start_time;

	start_time = check_time();
	while (check_time() - start_time < time)
		usleep(500);
	return (0);
}

size_t	check_time(void)
{
	struct timeval	tv;

	if(gettimeofday(&tv, NULL) < 0)
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
