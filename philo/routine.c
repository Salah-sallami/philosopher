/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaheddinesallami <salaheddinesallami@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:35:20 by salaheddine       #+#    #+#             */
/*   Updated: 2025/08/09 10:25:35 by salaheddine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	output_message(t_philo *phil, char *message)
{
	long long	timestamp;

	pthread_mutex_lock(&phil->sim_data->output_mutex);
	if (!phil->sim_data->termination_flag)
	{
		timestamp = current_timestamp() - phil->sim_data->simulation_start;
		printf("%lld %d %s\n", timestamp, phil->philo_id, message);
	}
	pthread_mutex_unlock(&phil->sim_data->output_mutex);
}

void	precise_wait(long ms)
{
	long long	start;

	start = current_timestamp();
	while (current_timestamp() - start < ms)
		usleep(200);
}

void	consume_meal(t_philo *phil)
{
	pthread_mutex_lock(&phil->left_utensil);
	output_message(phil, "has taken a fork");
	pthread_mutex_lock(phil->right_utensil);
	output_message(phil, "has taken a fork");
	output_message(phil, "is eating");
	phil->previous_meal_time = current_timestamp();
	phil->meal_count++;
	precise_wait(phil->sim_data->eating_duration);
	pthread_mutex_unlock(&phil->left_utensil);
	pthread_mutex_unlock(phil->right_utensil);
}

void	*philo_lifecycle(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	if (phil->philo_id % 2 == 0)
	{
		usleep(100);
	}
	while (!phil->sim_data->termination_flag)
	{
		consume_meal(phil);
		if (phil->sim_data->required_meals > 0
			&& phil->meal_count >= phil->sim_data->required_meals)
		{
			break ;
		}
		output_message(phil, "is sleeping");
		precise_wait(phil->sim_data->sleep_duration);
		output_message(phil, "is thinking");
	}
	return (NULL);
}
