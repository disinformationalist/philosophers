/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:00:59 by jhotchki          #+#    #+#             */
/*   Updated: 2024/05/15 12:01:02 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_p_mutexes_i(t_info *info, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&info->philos[i].philo_mtx);
}

void	destroy_f_mutexes_i(t_info *info, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&info->forks[i].fork);
}

int	join_threads_i(t_info *info, int i)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		if (pthread_join(info->philos[j].thread_num, NULL))
			return (1);
	}
	return (0);
}

void	clear(t_info *info)
{
	pthread_mutex_destroy(&info->print_mtx);
	pthread_mutex_destroy(&info->info_mtx);
	if (info->forks)
		free(info->forks);
	if (info->philos)
		free(info->philos);
}

void	clear_all(t_info *info)
{
	destroy_p_mutexes_i(info, info->total_philos);
	destroy_f_mutexes_i(info, info->total_philos);
	pthread_mutex_destroy(&info->print_mtx);
	pthread_mutex_destroy(&info->info_mtx);
	if (info->forks)
		free(info->forks);
	if (info->philos)
		free(info->philos);
}
