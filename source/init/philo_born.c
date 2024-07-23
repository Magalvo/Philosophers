#include "../../include/philosophers.h"

void	philo_init(t_table *table, t_philo *philo, int philo_id)
{
	philo[philo_id].philo_id = philo_id;
	philo[philo_id].nbr_of_meals = -1;
	philo[philo_id].eaten_meals = 0;
	philo[philo_id].nbr_of_forks = table->philo_nbr;
}

void	status_quo_init(t_table *table, t_philo *philo, int philo_id)
{
	(void)table;
	philo[philo_id].dead = false;
	philo[philo_id].eating = false;
	philo[philo_id].tinking = false;
	philo[philo_id].sleeping = false;
}

void	t_stamps_init(t_table *table, t_philo *philo, int philo_id, char **argv)
{
	(void)table;
	philo[philo_id].start_t = check_time();
	philo[philo_id].last_meal = check_time();
	philo[philo_id].t_to_die = ft_atoi(argv[2]);
	philo[philo_id].t_to_eat = ft_atoi(argv[3]);
	philo[philo_id].t_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo[philo_id].nbr_of_meals = ft_atoi(argv[5]);
	else
		philo[philo_id].nbr_of_meals = -1;
}

void	mut_init(t_table *table, t_philo *philo, int philo_id)
{
	(void)table;
	philo[philo_id].dead_gate = &table->dead_gate;
	philo[philo_id].meal_gate = &table->meal_gate;
	philo[philo_id].write_gate = &table->write_gate;
	philo[philo_id].l_fork = &table->forks[philo_id];
	if (philo_id == 0)
		philo[philo_id].l_fork = &table->forks[table->philo_nbr - 1];
	else
		philo[philo_id].l_fork = &table->forks[philo_id - 1];
}

void	philo_born(t_table *table, int philo_id, char **argv)
{
	t_philo	*philo;

	philo = &table->philos[philo_id];
	philo_init(table, philo, philo_id);
	status_quo_init(table, philo, philo_id);
	t_stamps_init(table, philo, philo_id, argv);
	mut_init(table, philo, philo_id);
}
