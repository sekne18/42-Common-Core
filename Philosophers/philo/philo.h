

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILOS 250

struct s_data;

typedef enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
	DIED,
	TAKE_FORK,
}	t_status;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				someone_died;
	int				all_ate_enough;
	long long		start_time;
	pthread_mutex_t	forks[MAX_PHILOS];
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			philos[MAX_PHILOS];
}	t_data;

/* main.c */
int			main(int argc, char **argv);

/* init.c */
int			init_data(t_data *data, char **argv, int argc);
void		init_philos(t_data *data);
void		cleanup_mutexes(t_data *data);

/* simulation.c */
int			start_simulation(t_data *data);
void		*philosopher_routine(void *arg);
void		*single_philo_routine(void *arg);

/* actions.c */
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		drop_forks(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		think(t_philo *philo);

/* monitor.c */
void		*monitor_routine(void *arg);
int			check_death(t_data *data);
int			check_all_ate(t_data *data);

/* utils.c */
long long	get_time(void);
void		smart_sleep(long long time_to_sleep, t_data *data);
void		print_status(t_philo *philo, t_status status);
int			ft_atoi(const char *str);
int			is_valid_args(char **argv, int argc);

#endif