/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:02:17 by jhotchki          #+#    #+#             */
/*   Updated: 2024/05/15 12:02:18 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_long(pthread_mutex_t *mutex, long *dest, long val)
{
	pthread_mutex_lock(mutex);
	*dest = val;
	pthread_mutex_unlock(mutex);
}

void	set_val(pthread_mutex_t *mutex, bool *dest, bool val)
{
	pthread_mutex_lock(mutex);
	*dest = val;
	pthread_mutex_unlock(mutex);
}

void	increase_val(pthread_mutex_t *mutex, long *val)
{
	pthread_mutex_lock(mutex);
	(*val)++;
	pthread_mutex_unlock(mutex);
}
