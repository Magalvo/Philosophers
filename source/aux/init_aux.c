/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:29:21 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/30 10:50:59 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	ft_usleep(size_t time)
{
	struct timeval		start_time;
	struct timeval		current_time;
	long long			elapsed_time;

	elapsed_time = 0;
	if (gettimeofday (&start_time, NULL) < 0)
	{
		perror ("gettimeofday failed");
		return ;
	}
	while (elapsed_time < (long long)time)
	{
		usleep (500);
		if (gettimeofday (&current_time, NULL) < 0)
		{
			perror("gettimeofday failed");
			return ;
		}
		elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000LL + \
						(current_time.tv_usec - start_time.tv_usec) / 1000LL;
	}
}

size_t	check_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
	{
		perror("gettimeofday failed");
		return (0);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	timed_message(char *message, t_philo *philo)
{
	size_t	start_time;

	pthread_mutex_lock(philo->write_gate);
	start_time = check_time() - philo->start_t;
	if (!(*philo->dead) && philo->eating == 1)
		printf("%zu\t%d\t%s\n", start_time, philo->id, message);
	pthread_mutex_unlock(philo->write_gate);
}
