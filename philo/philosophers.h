/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaheddinesallami <salaheddinesallami@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:35:08 by salaheddine       #+#    #+#             */
/*   Updated: 2025/08/09 10:26:02 by salaheddine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_simulation;

typedef struct s_philo
{
	int					philo_id;
	pthread_t			worker_thread;
	long				previous_meal_time;
	int					meal_count;
	pthread_mutex_t		left_utensil;
	pthread_mutex_t		*right_utensil;
	struct s_simulation	*sim_data;
}						t_philo;

typedef struct s_simulation
{
	int					total_philosophers;
	int					death_timeout;
	int					sleep_duration;
	int					eating_duration;
	int					required_meals;
	long				simulation_start;
	int					termination_flag;
	pthread_mutex_t		output_mutex;
	t_philo				*philos;
}						t_simulation;

// utils
int						validate_input(char **av);
int						str_to_int(const char *av);
long long				current_timestamp(void);
int						check_digit(int c);
int						check_whitespace(char c);
int						single_philosopher_case(t_simulation *sim);

// error
int						display_error(char *str, t_simulation *sim);
void					cleanup_resources(t_simulation *sim);

// routine & monitor
void					*philo_lifecycle(void *arg);
void					*death_monitor(void *arg);

#endif
