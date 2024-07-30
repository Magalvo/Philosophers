/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:28:28 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/29 16:56:21 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

int	check_full_belley(t_philo *philos)
{
	int	i;
	int	full_belly;

	i = 0;
	full_belly = 0;
	if (philos[0].max_meals == -1)
		return (0);
	while (i < philos[0].philo_nbr)
	{
		pthread_mutex_lock(philos[i].meal_gate);
		if (philos[i].eaten_meals >= philos[i].max_meals)
			full_belly++;
		pthread_mutex_unlock(philos[i].meal_gate);
		i++;
	}
	if (full_belly == philos[0].philo_nbr)
	{
		pthread_mutex_lock(philos[0].dead_gate);
		*philos[0].dead = 1;
		pthread_mutex_unlock(philos[0].dead_gate);
		return (1);
	}
	return (0);
}

int	dead_check(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].philo_nbr)
	{
		if (starv_o_meter(&philos[i], philos[i].t_to_die))
		{
			timed_message(" died *.*", &philos[i]);
			pthread_mutex_lock(philos[0].dead_gate);
			*philos[0].dead = 1;
			pthread_mutex_unlock(philos[0].dead_gate);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*socrates(void *pointer)
{
	t_table	*table;

	table = (t_table *)pointer;
	while (!table->dead_stop)
	{
		if (dead_check (table->philos) || check_full_belley (table->philos))
		{
			table->dead_stop = 1;
			break ;
		}
	}
	return (NULL);
}
