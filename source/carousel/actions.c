
#include "../../include/philosophers.h"

void	think(t_philo *philo)
{
	timed_message("%d is thinking\n", philo);
}

void	dream(t_philo *philo)
{
	timed_message("%d is dreaming\n", philo);
	ft_usleep(philo->t_to_sleep);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	timed_message("has taken right fork", philo);
	if (philo->nbr_of_forks == 1)
	{
		ft_usleep(philo->t_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	timed_message("has taken left fork", philo);
	philo->eating = true;
	timed_message("eating", philo);
	pthread_mutex_lock(philo->meal_gate);
	philo->last_meal = check_time();
	philo->eaten_meals++;
	pthread_mutex_unlock(philo->meal_gate);
	ft_usleep(philo->t_to_eat);
	philo->eating = false;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
