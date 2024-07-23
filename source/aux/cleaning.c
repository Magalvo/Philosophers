#include "../../include/philosophers.h"
/* void	error_free(t_stack *, char **argv, bool flag_argc_2)
{
	free_stack(a, argv, flag_argc_2);
	exit(1);
} */

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->write_gate);
	pthread_mutex_destroy(&table->dead_gate);
	pthread_mutex_destroy(&table->meal_gate);
}
