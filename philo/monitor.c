/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaheddinesallami <salaheddinesallami@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:35:02 by salaheddine       #+#    #+#             */
/*   Updated: 2025/08/09 10:25:35 by salaheddine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philosopher_death(t_simulation *sim, int index)
{
	long	current_time;

	current_time = current_timestamp();
	if ((current_time
			- sim->philos[index].previous_meal_time) > sim->death_timeout)
	{
		sim->termination_flag = 1;
		pthread_mutex_lock(&sim->output_mutex);
		printf("%ld %d died\n", current_time - sim->simulation_start,
			sim->philos[index].philo_id);
		pthread_mutex_unlock(&sim->output_mutex);
		return (1);
	}
	return (0);
}

int	check_all_satisfied(t_simulation *sim)
{
	int	index;
	int	satisfied_count;

	index = 0;
	satisfied_count = 0;
	while (index < sim->total_philosophers)
	{
		if (sim->required_meals > 0
			&& sim->philos[index].meal_count >= sim->required_meals)
			satisfied_count++;
		index++;
	}
	if (sim->required_meals > 0 && satisfied_count == sim->total_philosophers)
	{
		sim->termination_flag = 1;
		return (1);
	}
	return (0);
}

void	*death_monitor(void *arg)
{
	t_simulation	*sim;
	int				index;

	sim = (t_simulation *)arg;
	while (!sim->termination_flag)
	{
		index = 0;
		while (index < sim->total_philosophers)
		{
			if (check_philosopher_death(sim, index))
				return (NULL);
			index++;
		}
		if (check_all_satisfied(sim))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
