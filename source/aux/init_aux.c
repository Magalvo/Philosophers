/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:29:21 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/30 13:38:31 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/* int	ft_usleep(size_t time)
{
	struct timeval		start_time;
	struct timeval		current_time;
	long long			elapsed_time;

	elapsed_time = 0;
	if (gettimeofday (&start_time, NULL) < 0)
	{
		perror ("gettimeofday failed");
		return (1);
	}
	while (elapsed_time < (long long)time)
	{
		usleep (500);
		if (gettimeofday (&current_time, NULL) < 0)
		{
			perror("gettimeofday failed");
			return (1);
		}
		elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000LL + \
						(current_time.tv_usec - start_time.tv_usec) / 1000LL;
	}
	return (0);
} */

int	ft_usleep(size_t time)
{
	size_t	curr_t;

	curr_t = check_time();
	while((check_time() - curr_t) < time)
		usleep(500);
	return (0);
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

void	timed_message(char *message, char *color, t_philo *philo)
{
	size_t	start_time;

	pthread_mutex_lock(philo->write_gate);
	start_time = check_time() - philo->start_t;
	if (check_vitals(philo))
	{
		pthread_mutex_unlock(philo->write_gate);
		return ;
	}
	if (philo->eating == 1)
		printf("%s%zu\t%d\t%s\n", color, start_time, philo->id, message);
	else if ( philo->sleeping == 1)
		printf("%s%zu\t%d\t%s\n", color, start_time, philo->id, message);
	else if ( philo->thinking == 1)
		printf("%s%zu\t%d\t%s\n", color, start_time, philo->id, message);
	else
		printf("%s%zu\t%d\t%s\n", color, start_time, philo->id, message);
	pthread_mutex_unlock(philo->write_gate);
}
