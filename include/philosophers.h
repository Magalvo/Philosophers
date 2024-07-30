/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:53:07 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/30 13:55:45 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

# define TABLE_CAP 200

# define RST		"\e[0m"
# define BLD		"\e[1m"
# define FNT		"\e[2m"
# define ITL		"\e[3m"
# define UDL		"\e[4m"

# define BLACK		"\e[30m"
# define RED    	"\e[31m"
# define GREEN		"\e[32m"
# define YELLOW		"\e[33m"
# define BLUE		"\e[34m"
# define MAGENTA	"\e[35m"
# define CYAN		"\e[36m"
# define GRAY		"\e[90m"
# define WHITE		"\e[97m"

struct			s_philo
{
	int				id;
	int				philo_nbr;
	int				eaten_meals;
	int				*dead;
	int				eating;
	int				thinking;
	int				sleeping;
	int				max_meals;
	size_t			start_t;
	size_t			last_meal;
	size_t			t_to_die;
	size_t			t_to_eat;
	size_t			t_to_sleep;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*dead_gate;
	pthread_mutex_t	*meal_gate;
	pthread_mutex_t	*write_gate;
};

struct			s_table
{
	int				philo_nbr;
	int				dead_stop;
	size_t			t_to_die;
	size_t			t_to_eat;
	size_t			t_to_sleep;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_gate;
	pthread_mutex_t	meal_gate;
	pthread_mutex_t	write_gate;
};

//============================= AUXILIARY FUNCTIONS =====================//
void					timed_message(char *message, char *color, t_philo *philo);
void					mutex_stop(char *str, t_table *table, \
							pthread_mutex_t *forks);
void					ft_putstr_fd(char *s, int fd);
int						ft_usleep(size_t time);
int						ft_atoi(const char *str);
int						check_args(char *argv);
long					ft_atol(const char *str);
size_t					check_time(void);

//============================= INITIALIZATION FUNCTIONS ================//
void					philo_born(t_philo *philo, t_table *table, \
							char **argv, int id);
int						check_data(char **argv);
int						init_philos(t_table *table, char **argv);

//============================= MUTEX FUNCTIONS =========================//
void					mutex_start(t_table *table);

//============================= MAIN FUNCTIONS ==========================//
void					think(t_philo *philo);
void					dream(t_philo *philo);
void					eat(t_philo *philo);
void					*socrates(void *pointer);
int						go_init(t_table *table);
int						check_full_belley(t_philo *philos);
int						starv_o_meter(t_philo *philo, size_t t_to_die);
int						dead_check(t_philo *philos);
int						check_vitals(t_philo *philo);

#endif
