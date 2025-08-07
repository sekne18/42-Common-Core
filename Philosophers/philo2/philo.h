/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:17:57 by jans              #+#    #+#             */
/*   Updated: 2025/01/20 14:45:07 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
}						t_philo_status;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_time_code;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	pthread_mutex_t		philo_mutex;
	t_table				*table;
}						t_philo;

struct					s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				start_simulation;
	long				threads_running_nbr;
	bool				end_simulation;
	bool				all_threads_ready;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		write_mutex;
	pthread_t			monitor_thread;
	t_fork				*forks;
	t_philo				*philos;
};

int						parse_input(t_table *table, char **argv, int opt);
long					ft_atol(const char *nptr);
int						init_data(t_table *table);
void					assign_forks(t_philo *philo, t_fork *forks,
							int philo_pos);
int						philo_init(t_table *table);
void					*eating_simulation(void *data);
int						start_eating(t_table *table);
void					wait_all_threads(t_table *table);
long					gettime(t_time_code time_code);
void					precise_usleep(long usec, t_table *table);
void					write_status(t_philo_status status, t_philo *philo);
bool					sim_done(t_table *table);
void					thinking(t_philo *philo, bool pre_sim);
void					eat(t_philo *philo);
void					*monitor(void *data);
bool					all_philos_full(t_table *table);
bool					philo_dead(t_philo *philo);
void					*single_philo_simulation(void *data);
long					get_time(pthread_mutex_t *mutex, long *value);
void					set_time(pthread_mutex_t *mutex, long *dest,
							long value);
bool					get_bool(pthread_mutex_t *mutex, bool *value);
void					set_bool(pthread_mutex_t *mutex, bool *dest,
							bool value);
bool					all_threads_running(pthread_mutex_t *mutex,
							long *threads, long philo_nbr);
void					inc_threads(pthread_mutex_t *mutex, long *value);
void					desync_philos(t_philo *philo);
void					clean(t_table *table, int created_threads,
							bool monitor_created);
void					join_threads(t_table *table,
							int created_threads, bool monitor_created);
int						create_threads(t_table *table);
int						valid_input(char **argv, int opt);
int						ft_isdigit(char *str);

#endif
