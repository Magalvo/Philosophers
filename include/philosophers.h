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
typedef struct s_philo	t_philo;

#define TABLE_CAP 200
struct			s_philo
{
	int				philo_id;
	int				nbr_of_forks;
	int				nbr_of_meals;
	int				eaten_meals;
	bool			dead;
	bool			eating;
	bool			tinking;
	bool			sleeping;
	size_t			start_t;
	size_t			last_meal;
	size_t			t_to_die;
	size_t			t_to_eat;
	size_t			t_to_sleep;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t *l_fork;
	pthread_mutex_t	*dead_gate;
	pthread_mutex_t *meal_gate;
	pthread_mutex_t *write_gate;
};

struct			s_table
{
	int					philo_nbr;
	bool				dead_stop;
	t_philo				philos[TABLE_CAP];
	pthread_mutex_t		forks[TABLE_CAP];
	pthread_mutex_t		dead_gate;
	pthread_mutex_t 	meal_gate;
	pthread_mutex_t 	write_gate;
};

//============================= AUXILIARY FUNCTIONS =============================//
long					ft_atol(const char *str);
int						ft_atoi(const char *str);
int						ft_usleep(size_t time);
size_t					check_time(void);
int						check_args(char *argv);
void					timed_message(char *message, t_philo *philo);
void					destroy_mutex(t_table *table);

//============================= INITIALIZATION FUNCTIONS =============================//
int						check_data(char **argv);
void					philo_born(t_table *table, int philo_id, char **argv);

//============================= MUTEX FUNCTIONS =============================//
void					mutex_start(t_table *table);

//============================= MAIN FUNCTIONS =============================//
void					think(t_philo *philo);
void					dream(t_philo *philo);
void					eat(t_philo *philo);
int						go_init(t_table *table);
void					*socrates(void *pointer);

#endif
