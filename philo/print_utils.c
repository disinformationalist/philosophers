/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:02:06 by jhotchki          #+#    #+#             */
/*   Updated: 2024/05/15 12:02:08 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_putstr_color_fd(int fd, char *s, char *color)
{
	int	len;

	len = 0;
	write(fd, color, ft_strlen(color));
	while (*s)
		len += write(fd, s++, 1);
	write(fd, RESET, ft_strlen(RESET));
	return (len);
}

void	print_status(t_status status, t_philo *philo)
{
	long	tp;
	long	st;

	st = philo->info->start_time;
	tp = get_time(philo->info) - check_long(&philo->info->info_mtx, &st);
	if (check_val(&philo->philo_mtx, &philo->is_full))
		return ;
	pthread_mutex_lock(&philo->info->print_mtx);
	if (status == DEAD)
		printf("%ld"RED" %d is dead\n"RESET, tp, philo->philo_num);
	else if (!sim_over(philo->info))
	{
		if (status == TAKE_1ST_FORK || status == TAKE_2ND_FORK)
			printf("%ld"" %d has taken a fork\n", tp, philo->philo_num);
		else if (status == EATING)
			printf("%ld"YELLOW" %d is eating\n"RESET, tp, philo->philo_num);
		else if (status == SLEEPING)
			printf("%ld"BLUE" %d is sleeping\n"RESET, tp, philo->philo_num);
		else if (status == THINKING)
			printf("%ld"GREEN" %d is thinking\n"RESET, tp, philo->philo_num);
	}
	pthread_mutex_unlock(&philo->info->print_mtx);
}
