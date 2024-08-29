/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:01:45 by jhotchki          #+#    #+#             */
/*   Updated: 2024/05/15 12:01:47 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include "ansi_colors.h"

# define MAX_INT 2147483647
# define T_LIM 60
# define PHILO_LIM 200
# define PHILO_LIM_ERR "Min number of philos: 1, Max number of philos: 200\n"
# define SYNTAX_ERROR "Syntax: ./philo <number_of_philosphers>\n \
<time_to_die> <time_to_eat> <time_to_sleep>\n \
[number_of_times_each philosopher_must_eat]\n"
# define INVALID_INP "Values must be positive numbers, maximum is int max\n"
# define TIME_ERR "Time cannot be less than 60 millisecond\n"
# define MEALS_ERR "If entered, the number of meals must be greater than 0 \
and at most int max\n"

typedef struct s_info	t_info;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_num;

}	t_fork;

typedef struct s_philo
{
	int				philo_num;
	long			meals;
	bool			is_full;
	bool			is_eating;
	long			last_eat_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_num;
	pthread_mutex_t	philo_mtx;
	t_info			*info;
}	t_philo;

typedef struct s_info
{
	long			total_philos;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meal_limit;
	bool			synched;
	bool			end_sim;
	long			running;
	pthread_mutex_t	info_mtx;
	pthread_mutex_t	print_mtx;
	t_philo			*philos;
	t_fork			*forks;
	pthread_t		monitor;
}	t_info;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_1ST_FORK,
	TAKE_2ND_FORK,
	DEAD,	
}	t_status;

/***INIT***/
int		input_info(t_info *info, char **av);
int		init(t_info *info);

/***PRINT UTILS***/
size_t	ft_putstr_color_fd(int fd, char *s, char *color);
void	print_status(t_status status, t_philo *philo);

/***UTILS***/
int		start_sim(t_info *info);
long	get_time(t_info *info);
void	new_sleep(long usec, t_info *info);

//get
bool	check_val(pthread_mutex_t *mutex, bool *val);
bool	sim_over(t_info *info);
bool	all_running(pthread_mutex_t *mutex, long *threads, long total_philos);
long	check_long(pthread_mutex_t *mutex, long *val);

//set
void	increase_val(pthread_mutex_t *mutex, long *val);
void	set_long(pthread_mutex_t *mutex, long *dest, long val);
void	set_val(pthread_mutex_t *mutex, bool *dest, bool val);

/***PHILO ACTIVITIES***/
void	eat(t_philo *philo);
void	think(t_philo *philo);
bool	is_dead(t_philo *philo);

/***CLEAN UP***/
int		error(char *msg);
void	destroy_p_mutexes_i(t_info *info, int i);
void	destroy_f_mutexes_i(t_info *info, int i);
int		join_threads_i(t_info *info, int i);
void	clear(t_info *info);
void	clear_all(t_info *info);

#endif
