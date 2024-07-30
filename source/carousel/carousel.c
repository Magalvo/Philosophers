/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carousel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:28:16 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/29 16:24:15 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

int	starv_o_meter(t_philo *philo, size_t t_to_die)
{
	pthread_mutex_lock(philo->meal_gate);
	if (check_time() - philo->last_meal >= t_to_die && !philo->eating)
		return (pthread_mutex_unlock(philo->meal_gate), 1);
	pthread_mutex_unlock(philo->meal_gate);
	return (0);
}

int	check_vitals(t_philo *philo)
{
	int	dead_status;

	pthread_mutex_lock(philo->dead_gate);
	dead_status = 0;
	if (*philo->dead == 1)
		dead_status = 1;
	pthread_mutex_unlock(philo->dead_gate);
	return (dead_status);
}

void	*philo_life(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!check_vitals(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (NULL);
}

int	go_init(t_table *table)
{
	pthread_t	waiter;
	int			i;

	i = 0;
	if (pthread_create(&waiter, NULL, &socrates, table) != 0)
		mutex_stop("*Waiter* Error on create", table, table->forks);
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philos[i].thread, NULL, \
			&philo_life, &table->philos[i]) != 0)
			mutex_stop("*Table* Error on create", table, table->forks);
		i++;
	}
	i = 0;
	if (pthread_join(waiter, NULL) != 0)
		mutex_stop("*Waiter* Error on join", table, table->forks);
	while (i < table->philo_nbr)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			mutex_stop("*Table* Error on join", table, table->forks);
		i++;
	}
	return (0);
}
