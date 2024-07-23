#include "../../include/philosophers.h"

void	timed_message(char *message, t_philo *philo)
{
	size_t	start_time;

	pthread_mutex_lock(philo->write_gate);
	start_time = check_time() - philo->start_t;
	if (!philo->dead)
		printf("%zu %d %s\n", start_time, philo->philo_id, message);
	pthread_mutex_lock(philo->write_gate);
}
