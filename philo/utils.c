/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:02:53 by jhotchki          #+#    #+#             */
/*   Updated: 2024/05/15 12:02:56 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

static long	ft_atol(const char *nptr)
{
	long	result;
	int		i;

	result = 0;
	i = spaces(nptr);
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	return (result);
}

int	input_info(t_info *info, char **av)
{
	info->total_philos = ft_atol(av[1]);
	if (info->total_philos > PHILO_LIM || info->total_philos <= 0)
		return (error(PHILO_LIM_ERR));
	info->time_to_die = ft_atol(av[2]);
	info->time_to_eat = ft_atol(av[3]);
	info->time_to_sleep = ft_atol(av[4]);
	if (info->time_to_die > MAX_INT || info->time_to_eat > MAX_INT \
	|| info->time_to_sleep > MAX_INT || info->total_philos > MAX_INT)
		return (error(INVALID_INP));
	if (info->time_to_die < T_LIM || info->time_to_eat < T_LIM \
	|| info->time_to_sleep < T_LIM)
		return (error(TIME_ERR));
	if (av[5])
	{
		info->meal_limit = ft_atol(av[5]);
		if (info->meal_limit > MAX_INT || info->meal_limit <= 0)
			return (error(MEALS_ERR));
	}
	return (0);
}

long	get_time(t_info *info)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		clear_all(info);
		return (-1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	new_sleep(long usec, t_info *info)
{
	long	start;
	long	time_passed;
	long	time_left;

	usec *= 1000;
	start = get_time(info) * 1000;
	while (get_time(info) * 1000 - start < usec)
	{
		if (sim_over(info))
			break ;
		time_passed = get_time(info) * 1000 - start;
		time_left = usec - time_passed;
		if (time_left > 1000)
			usleep(time_left / 2);
		else
		{
			while (get_time(info) * 1000 - start < usec)
				;
		}
	}
}
