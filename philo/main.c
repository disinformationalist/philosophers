/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:01:35 by jhotchki          #+#    #+#             */
/*   Updated: 2024/05/15 12:01:37 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *msg)
{
	ft_putstr_color_fd(2, msg, RED);
	return (EXIT_FAILURE);
}

static int	args_check(char **av)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	while (av[i])
	{
		j = 0;
		len = 0;
		if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (error(INVALID_INP));
			len++;
			j++;
		}
		if (len > 10)
			return (error(INVALID_INP));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 6 && ac != 5)
		return (error(SYNTAX_ERROR));
	if (args_check(av))
		return (EXIT_FAILURE);
	if (input_info(&info, av))
		return (EXIT_FAILURE);
	if (init(&info))
		return (EXIT_FAILURE);
	if (start_sim(&info))
	{
		clear_all(&info);
		return (EXIT_FAILURE);
	}
	clear_all(&info);
	return (EXIT_SUCCESS);
}
