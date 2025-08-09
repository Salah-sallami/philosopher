/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaheddinesallami <salaheddinesallami@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:34:20 by salaheddine       #+#    #+#             */
/*   Updated: 2025/08/09 10:25:35 by salaheddine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_simulation_threads(t_simulation *sim)
{
	int			i;
	pthread_t	death_watcher;

	i = 0;
	while (i < sim->total_philosophers)
	{
		if (!!pthread_create(&sim->philos[i].worker_thread, NULL,
				philo_lifecycle, &sim->philos[i]))
			return (display_error("Thread creation failed", sim), 0);
		usleep(20);
		i++;
	}
	if (!!pthread_create(&death_watcher, NULL, death_monitor, sim))
		return (display_error("Monitor thread creation failed", sim), 0);
	i = 0;
	while (i < sim->total_philosophers)
	{
		pthread_join(sim->philos[i].worker_thread, NULL);
		i++;
	}
	pthread_join(death_watcher, NULL);
	return (1);
}

int	initialize_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->simulation_start = current_timestamp();
	sim->termination_flag = 0;
	sim->philos = malloc(sizeof(t_philo) * sim->total_philosophers);
	if (!sim->philos)
		return (display_error("Malloc failed", NULL), 0);
	if (!!pthread_mutex_init(&sim->output_mutex, NULL))
		return (display_error("Mutex init failed", sim), 0);
	while (i < sim->total_philosophers)
	{
		sim->philos[i].philo_id = i + 1;
		sim->philos[i].meal_count = 0;
		sim->philos[i].previous_meal_time = sim->simulation_start;
		sim->philos[i].sim_data = sim;
		if (!!pthread_mutex_init(&sim->philos[i].left_utensil, NULL))
			return (display_error("Mutex init failed", sim), 0);
		if (i == sim->total_philosophers - 1)
			sim->philos[i].right_utensil = &sim->philos[0].left_utensil;
		else
			sim->philos[i].right_utensil = &sim->philos[i + 1].left_utensil;
		i++;
	}
	return (1);
}

int	process_arguments(t_simulation *sim, char **av)
{
	if (!validate_input(av))
		return (0);
	sim->total_philosophers = str_to_int(av[1]);
	sim->death_timeout = str_to_int(av[2]);
	sim->eating_duration = str_to_int(av[3]);
	sim->sleep_duration = str_to_int(av[4]);
	if (av[5])
	{
		sim->required_meals = str_to_int(av[5]);
		if (sim->required_meals <= 0)
			return (display_error("INVALID INPUT VALUES", NULL), 0);
	}
	else
	{
		sim->required_meals = -1;
	}
	if (sim->total_philosophers <= 0 || sim->total_philosophers > 200
		|| sim->death_timeout < 60 || sim->eating_duration < 60
		|| sim->sleep_duration < 60)
		return (display_error("INVALID INPUT VALUES", NULL), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (argc < 5 || argc > 6)
	{
		printf("\nUSAGE: ./philo <philo_count> <die_time>");
		printf(" <eat_time> <sleep_time> [<repeat_times>]\n");
		return (1);
	}
	if (!process_arguments(&simulation, argv))
		return (1);
	if (!initialize_simulation(&simulation))
		return (1);
	if (simulation.total_philosophers == 1)
	{
		single_philosopher_case(&simulation);
		cleanup_resources(&simulation);
		return (0);
	}
	if (!start_simulation_threads(&simulation))
		return (1);
	cleanup_resources(&simulation);
	return (0);
}
