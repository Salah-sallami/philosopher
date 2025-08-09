/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaheddinesallami <salaheddinesallami@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:35:26 by salaheddine       #+#    #+#             */
/*   Updated: 2025/08/09 10:25:35 by salaheddine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup_resources(t_simulation *sim)
{
	int	i;
	int	total_phil;

	total_phil = sim->total_philosophers;
	if (sim->philos)
	{
		i = 0;
		while (i < total_phil)
		{
			pthread_mutex_destroy(&sim->philos[i].left_utensil);
			i++;
		}
		free(sim->philos);
	}
	pthread_mutex_destroy(&sim->output_mutex);
}

int	display_error(char *str, t_simulation *sim)
{
	printf("%s\n", str);
	if (sim)
		cleanup_resources(sim);
	return (1);
}

int	check_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	check_digit(int c)
{
	return (c >= 48 && c <= 57);
}

int	str_to_int(const char *av)
{
	int	number;

	number = 0;
	while (check_whitespace(*av))
		av++;
	if (*av == '+')
		av++;
	else if (*av == '-' || !check_digit(*av))
		return (-1);
	while (check_digit(*av))
	{
		number = number * 10 + (*av - '0');
		av++;
	}
	while (check_whitespace(*av))
		av++;
	if (*av)
		return (-1);
	return (number);
}
