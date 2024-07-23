#include "../../include/philosophers.h"

int	starv_o_meter(t_philo *philo, size_t t_to_die)
{
	pthread_mutex_lock(philo->meal_gate);
	if (check_time() - philo->last_meal >= t_to_die
		&& philo->eating == false)
		return(pthread_mutex_unlock(philo->meal_gate), 1);
	pthread_mutex_unlock(philo->meal_gate);
	return (0);
}

int	dead_check(t_table *table)
{
	int	i;


	i = 0;
	while (i < table->philo_nbr)
	{
		if (starv_o_meter(&table->philos[i], table->philos[i].t_to_die))
		{
			timed_message("died", &table->philos[i]);
			pthread_mutex_lock(table->philos[i].dead_gate);
			table->philos[i].dead = true;
			pthread_mutex_unlock(table->philos[i].dead_gate);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_full_belley(t_table *table)
{
	int	i;
	int	full_belly;

	i = 0;
	full_belly = 0;
	if (table->philos->nbr_of_meals == -1)
		return (0);
	while (i < table->philo_nbr)
	{
		pthread_mutex_lock(table->philos[i].meal_gate);
		if (table->philos[i].eaten_meals >= table->philos[i].nbr_of_meals)
			full_belly++;
		pthread_mutex_unlock(table->philos[i].meal_gate);
		i++;
	}
	if (full_belly == table->philo_nbr)
	{
		pthread_mutex_lock(&table->dead_gate);
		table->dead_stop = true;
		pthread_mutex_unlock(&table->dead_gate);
		return (1);
	}
	return (0);
}
//? MONITOR
void	*socrates(void *pointer)
{
	t_table	*table;

	table = (t_table *)pointer;
	while (1)
	{
		if (dead_check(table) == 1 || check_full_belley(table) == 1)
			break ;
	}
	return (pointer);
}
