/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaheddinesallami <salaheddinesallami@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:35:34 by salaheddine       #+#    #+#             */
/*   Updated: 2025/08/08 19:35:36 by salaheddine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	validate_input(char **av)
{
	int	i;
	int	x;

	i = 1;
	while (av[i])
	{
		if (!av[i][0])
			return (display_error("INVALID INPUT VALUES", NULL), 0);
		x = 0;
		while (check_whitespace(av[i][x]))
			x++;
		while (av[i][x])
		{
			if (!check_digit(av[i][x]) && av[i][x] != '+'
				&& !check_whitespace(av[i][x]))
				return (display_error("INVALID INPUT VALUES", NULL), 0);
			x++;
		}
		i++;
	}
	return (1);
}

long long	current_timestamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (display_error("gettimeofday() FAILED", NULL), 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	single_philosopher_case(t_simulation *sim)
{
	long	start_moment;
	long	timestamp;

	start_moment = current_timestamp();
	timestamp = current_timestamp() - start_moment;
	printf("%ld 1 has taken a fork\n", timestamp);
	usleep(sim->death_timeout * 1000);
	timestamp = sim->death_timeout;
	printf("%ld 1 died\n", timestamp);
	return (0);
}
