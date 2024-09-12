/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:28:01 by dde-maga          #+#    #+#             */
/*   Updated: 2024/09/12 19:19:52 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	timed_message(" has taken a right fork", CYAN, philo);
	if (philo->philo_nbr == 1)
	{
		ft_usleep(philo->t_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	timed_message(" has taken a left fork", CYAN, philo);
	philo->eating = 1;
	timed_message(" is eating", GREEN, philo);
	pthread_mutex_lock(philo->meal_gate);
	philo->last_meal = check_time();
	philo->eaten_meals++;
	pthread_mutex_unlock(philo->meal_gate);
	ft_usleep(philo->t_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	dream(t_philo *philo)
{
		philo->sleeping = 1;
		timed_message(" is sleeping", BLUE, philo);
		ft_usleep(philo->t_to_sleep);
		philo->sleeping = 0;
}

void	think(t_philo *philo)
{
	philo->thinking = 1;
	timed_message(" is thinking", YELLOW, philo);
	philo->thinking = 0;
}
