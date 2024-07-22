#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>

typedef struct s_table	t_table;
typedef struct s_pilo	t_philo;

struct			s_philo
{
	int				philo_id;
	int				nbr_of_meals;
	int				eaten_meals;
	bool			dead;
	bool			eating;
	bool			tinking;
	bool			sleeping;
	size_t			start_t;
	size_t			t_to_die;
	size_t			t_to_eat;
	size_t			t_to_sleep;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t *l_fork;
	pthread_mutex_t	*dead_mut;
	pthread_mutex_t *meal_mut;
	pthread_mutex_t *write_mut;
};

struct			s_table
{
	int				forks;
	int				philo_nbr;
	bool			dead_stop;
	t_philo			*philos;
	pthread_mutex_t	dead_mut;
	pthread_mutex_t meal_mut;
	pthread_mutex_t write_mut;
};

#endif