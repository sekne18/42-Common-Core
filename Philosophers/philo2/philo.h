
#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct s_table;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
} 						t_fork;

typedef struct s_philo
{
	int				id;
	long			meals_counter;
	long			last_meal_time;
	bool			full;
	pthread_t		thread_id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_table	*table;
} 						t_philo;

typedef struct s_table
{
	int				philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_limit_meals;
	bool			end_simulation;
	long			start_simulation;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	write_mutex;
} 						t_table;

// utils.c
long	get_timestamp(void);
void	ft_usleep(long ms);
int		parse_input(t_table *table, char **argv, bool has_limit);
int		init_data(t_table *table);
void	clean(t_table *table);

// philo.c
void	print_status(t_philo *philo, char *msg);
void	eat(t_philo *philo);
void	*philo_life(void *arg);

// monitor.c
void	*monitor(void *arg);

#endif
