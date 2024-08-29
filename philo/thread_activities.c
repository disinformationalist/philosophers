/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_activities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:02:44 by jhotchki          #+#    #+#             */
/*   Updated: 2024/05/15 12:02:47 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_status(TAKE_1ST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	print_status(TAKE_2ND_FORK, philo);
}

void	eat(t_philo *philo)
{
	grab_forks(philo);
	set_val(&philo->philo_mtx, &philo->is_eating, true);
	set_long(&philo->philo_mtx, &philo->last_eat_time, get_time(philo->info));
	philo->meals++;
	print_status(EATING, philo);
	new_sleep(philo->info->time_to_eat, philo->info);
	if (philo->meals == philo->info->meal_limit)
		set_val(&philo->philo_mtx, &philo->is_full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
	set_val(&philo->philo_mtx, &philo->is_eating, false);
}

void	think(t_philo *philo)
{
	long	think_time;
	long	sleep_time;
	long	eat_time;
	long	die_time;

	print_status(THINKING, philo);
	sleep_time = philo->info->time_to_sleep;
	eat_time = philo->info->time_to_eat;
	think_time = eat_time * 2 - sleep_time;
	die_time = philo->info->time_to_die;
	if (think_time < 0)
		think_time = 0;
	if (philo->info->total_philos % 2 == 0 && \
	(die_time <= sleep_time + eat_time + 50))
		return ;
	else
		new_sleep(think_time, philo->info);
}

bool	is_dead(t_philo *philo)
{
	long	t_passed;

	if (check_val(&philo->philo_mtx, &philo->is_full))
		return (0);
	t_passed = get_time(philo->info) - \
	check_long(&philo->philo_mtx, &philo->last_eat_time);
	if (t_passed > philo->info->time_to_die \
	&& !check_val(&philo->philo_mtx, &philo->is_eating))
		return (1);
	return (0);
}
