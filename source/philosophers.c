#include "../include/philosophers.h"

void	mutex_start(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->write_gate, NULL);
	pthread_mutex_init(&table->dead_gate, NULL);
	pthread_mutex_init(&table->meal_gate, NULL);
}

int	init_table(t_table *table, char **argv)
{
	long	philo_nbr;
	int		i;

	i = 0;
	philo_nbr = ft_atoi(argv[1]);
	if (philo_nbr > TABLE_CAP)
		return (write(2, "Too Many Guests\n", 16), 1);
	table->philo_nbr = philo_nbr;
	table->dead_stop = false;
	mutex_start(table);
	while (i < philo_nbr)
	{
		philo_born(table, i, argv);
		i++;
	}
	return (0);
}

int 	main(int argc, char **argv)
{
	t_table		table;

	if (argc != 6 && argc != 5)
		return(write(2, "Give More Info Please\n", 23), 1);
	else if (check_data(argv) == 1)
		return (write(2, "Invalid Arguments\n", 19), 1);
	init_table(&table, argv);
	go_init(&table);
	destroy_mutex(&table);
	return (0);
}
