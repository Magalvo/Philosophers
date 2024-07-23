#include "../../include/philosophers.h"

int	check_vitals(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_gate);
	if (philo->dead == true)
		return (pthread_mutex_unlock(philo->dead_gate), 1);
	pthread_mutex_unlock(philo->dead_gate);
	return (0);
}

void	*philo_life(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (!check_vitals(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

int	go_init(t_table *table)
{
	pthread_t	waiter;
	int			i;

	i = 0;
	if (pthread_create(&waiter, NULL, &socrates, table) != 0)
		return (1);
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &philo_life, &table->philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	if (pthread_join(waiter, NULL) != 0)
		return (1);
	while (i < table->philo_nbr)
	{
		if(pthread_join(table->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
