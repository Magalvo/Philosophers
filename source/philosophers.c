/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:29:06 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/30 13:56:10 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_table(t_table *table, int argc, char **argv)
{
	if (argc != 6 && argc != 5)
		return (write(2, "Give More Info Please\n", 23), 1);
	else if (check_data(argv) == 1)
		return (write(2, "Invalid Arguments\n", 19), 1);
	table->philo_nbr = ft_atoi(argv[1]);
	if (!table->philo_nbr || table->philo_nbr > TABLE_CAP)
		return (write(2, "Too Many Guests\n", 16), 1);
	table->philos = malloc(table->philo_nbr * sizeof(t_philo));
	table->forks = malloc(table->philo_nbr * sizeof(pthread_mutex_t));
	if (table->philos == NULL || table->forks == NULL)
		return (perror("Failed to allocate memory"), 1);
	table->dead_stop = 0;
	return (0);
}

void	mutex_start(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
		pthread_mutex_init(&table->forks[i++], NULL);
	pthread_mutex_init(&table->write_gate, NULL);
	pthread_mutex_init(&table->dead_gate, NULL);
	pthread_mutex_init(&table->meal_gate, NULL);
}

void	cleaner(t_table *table)
{
	if (!table)
		return ;
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (init_table (&table, argc, argv) != 0)
		return (1);
	mutex_start (&table);
	init_philos (&table, argv);
	go_init (&table);
	mutex_stop (NULL, &table, table.forks);
	cleaner (&table);
	return (0);
}
