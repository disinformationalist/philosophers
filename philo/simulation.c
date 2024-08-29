/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:02:31 by jhotchki          #+#    #+#             */
/*   Updated: 2024/05/15 12:02:36 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*only_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_val(&philo->info->info_mtx, &philo->info->synched))
		;
	set_long(&philo->philo_mtx, &philo->last_eat_time, get_time(philo->info));
	increase_val(&philo->info->info_mtx, &philo->info->running);
	print_status(TAKE_1ST_FORK, philo);
	while (!sim_over(philo->info))
		new_sleep(200, philo->info);
	return (NULL);
}

void	*monitoring(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	while (!all_running(&info->info_mtx, &info->running, info->total_philos))
		;
	while (!sim_over(info))
	{
		i = -1;
		while (++i < info->total_philos && !sim_over(info))
		{
			if (is_dead(&info->philos[i]))
			{
				set_val(&info->info_mtx, &info->end_sim, true);
				print_status(DEAD, &info->philos[i]);
			}
		}
	}
	return (NULL);
}

void	*sim(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_val(&philo->info->info_mtx, &philo->info->synched))
		;
	set_long(&philo->philo_mtx, &philo->last_eat_time, get_time(philo->info));
	increase_val(&philo->info->info_mtx, &philo->info->running);
	print_status(THINKING, philo);
	while (!sim_over(philo->info))
	{
		if (check_val(&philo->philo_mtx, &philo->is_full))
			break ;
		eat(philo);
		print_status(SLEEPING, philo);
		new_sleep(philo->info->time_to_sleep, philo->info);
		think(philo);
	}
	return (NULL);
}

int	continue_sim(t_info *info)
{
	if (pthread_create(&info->monitor, NULL, monitoring, info))
	{
		join_threads_i(info, info->total_philos);
		return (error("Error creating monitor thread\n"));
	}
	info->start_time = get_time(info);
	set_val(&info->info_mtx, &info->synched, true);
	if (join_threads_i(info, info->total_philos))
	{
		pthread_join(info->monitor, NULL);
		return (error("Error joining threads\n"));
	}
	set_val(&info->info_mtx, &info->end_sim, true);
	if (pthread_join(info->monitor, NULL))
		return (error("Error joining threads\n"));
	return (0);
}

int	start_sim(t_info *info)
{
	int	i;

	i = -1;
	if (info->total_philos == 1)
	{
		if (pthread_create(&info->philos[0].thread_num, \
		NULL, only_one, &info->philos[0]))
			return (error("Error creating philo thread\n"));
	}
	else
	{
		while (++i < info->total_philos)
		{
			if (pthread_create(&info->philos[i].thread_num, \
			NULL, sim, &info->philos[i]))
			{
				join_threads_i(info, i);
				return (error("Error creating philo threads\n"));
			}
		}
	}
	if (continue_sim(info))
		return (1);
	return (0);
}
