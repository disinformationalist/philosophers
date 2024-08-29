/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:01:16 by jhotchki          #+#    #+#             */
/*   Updated: 2024/05/15 12:01:18 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_val(pthread_mutex_t *mutex, bool *val)
{
	bool	current;

	pthread_mutex_lock(mutex);
	current = *val;
	pthread_mutex_unlock(mutex);
	return (current);
}

bool	sim_over(t_info *info)
{
	return (check_val(&info->info_mtx, &info->end_sim));
}

long	check_long(pthread_mutex_t *mutex, long *val)
{
	long	current;

	pthread_mutex_lock(mutex);
	current = *val;
	pthread_mutex_unlock(mutex);
	return (current);
}

bool	all_running(pthread_mutex_t *mutex, long *threads, long total_philos)
{
	bool	ret;

	ret = 0;
	pthread_mutex_lock(mutex);
	if (*threads == total_philos)
		ret = 1;
	pthread_mutex_unlock(mutex);
	return (ret);
}
