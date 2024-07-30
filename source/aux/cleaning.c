/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:29:37 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/29 15:48:20 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	mutex_stop(char *str, t_table *table, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		ft_putstr_fd(str, 2);
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&table->write_gate);
	pthread_mutex_destroy(&table->dead_gate);
	pthread_mutex_destroy(&table->meal_gate);
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
