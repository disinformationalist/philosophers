/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:01:26 by jhotchki          #+#    #+#             */
/*   Updated: 2024/05/15 12:01:28 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_n;

	philo_n = philo->info->total_philos;
	if (philo->philo_num % 2 == 0)
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % philo_n];
	}
	else
	{
		philo->first_fork = &forks[(i + 1) % philo_n];
		philo->second_fork = &forks[i];
	}
}

static int	init_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->total_philos)
	{
		info->philos[i].philo_num = i + 1;
		info->philos[i].meals = 0;
		info->philos[i].is_full = false;
		info->philos[i].is_eating = false;
		info->philos[i].info = info;
		if (pthread_mutex_init(&info->philos[i].philo_mtx, NULL))
		{
			destroy_f_mutexes_i(info, info->total_philos);
			destroy_p_mutexes_i(info, i);
			clear(info);
			return (error("Philo mutex init failure\n"));
		}
		set_forks(&info->philos[i], info->forks, i);
	}
	return (0);
}

static void	init_values(t_info *info)
{
	info->end_sim = false;
	info->running = 0;
	info->synched = false;
}

static int	mallocate(t_info *info)
{
	if (pthread_mutex_init(&info->info_mtx, NULL))
		return (error("Info mutex init failure"));
	if (pthread_mutex_init(&info->print_mtx, NULL))
	{
		pthread_mutex_destroy(&info->info_mtx);
		return (error("Print mutex init failure"));
	}
	info->philos = (t_philo *)malloc(info->total_philos * sizeof(t_philo));
	if (info->philos == NULL)
	{
		clear(info);
		return (error("Philo Malloc Error\n"));
	}
	info->forks = (t_fork *)malloc(info->total_philos * sizeof(t_fork));
	if (info->forks == NULL)
	{
		clear(info);
		return (error("Fork Malloc Error\n"));
	}
	return (0);
}

int	init(t_info *info)
{
	int		i;

	if (mallocate(info))
		return (1);
	init_values(info);
	i = -1;
	while (++i < info->total_philos)
	{
		if (pthread_mutex_init(&info->forks[i].fork, NULL))
		{
			destroy_f_mutexes_i(info, i);
			clear(info);
			return (error("Fork mutex init failure\n"));
		}
		info->forks[i].fork_num = i;
	}
	if (init_philos(info))
		return (1);
	return (0);
}
