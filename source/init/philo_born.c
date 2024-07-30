/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_born.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:28:46 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/29 15:39:00 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	philo_init(t_philo *philo, int id)
{
	philo->id = id + 1;
	philo->eaten_meals = 0;
}

void	status_quo_init(t_philo *philo)
{
	philo->eating = 0;
	philo->thinking = 0;
	philo->sleeping = 0;
}

void	t_stamps_init(t_philo *philo, char **argv)
{
	philo->start_t = check_time();
	philo->last_meal = philo->start_t;
	philo->t_to_die = ft_atoi(argv[2]);
	philo->t_to_eat = ft_atoi(argv[3]);
	philo->t_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->max_meals = ft_atoi(argv[5]);
	else
		philo->max_meals = -1;
}

void	philo_born(t_philo *philo, t_table *table, char **argv, int id)
{
	philo_init(philo, id);
	status_quo_init(philo);
	t_stamps_init(philo, argv);
	philo->dead = &table->dead_stop;
	philo->philo_nbr = table->philo_nbr;
	philo->dead_gate = &table->dead_gate;
	philo->meal_gate = &table->meal_gate;
	philo->write_gate = &table->write_gate;
	if (id == 0)
		table->philos[id].r_fork = \
			&table->forks[table->philos[id].philo_nbr - 1];
	else
		table->philos[id].r_fork = &table->forks[id - 1];
	philo->l_fork = &table->forks[id];
}

int	init_philos(t_table *table, char **argv)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].dead = &table->dead_stop;
		philo_born (&table->philos[i], table, argv, i);
		i++;
	}
	return (0);
}
