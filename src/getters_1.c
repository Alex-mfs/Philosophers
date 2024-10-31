/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:25:03 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/30 14:44:29 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	get_keep_iter(t_data *data)
{
	bool	keep_iterating;

	pthread_mutex_lock(&data->mut_keep_iter);
	keep_iterating = data->keep_iterating;
	pthread_mutex_unlock(&data->mut_keep_iter);
	return (keep_iterating);
}

int	get_philos_nbr(t_data *data)
{
	int	philos_nbr;

	pthread_mutex_lock(&data->mut_philos_nbr);
	philos_nbr = data->philos_nbr;
	pthread_mutex_unlock(&data->mut_philos_nbr);
	return (philos_nbr);
}

t_state	get_philo_state(t_philo *philo)
{
	t_state	state;

	pthread_mutex_lock(&philo->mut_state);
	state = philo->state;
	pthread_mutex_unlock(&philo->mut_state);
	return (state);
}

int	get_nbr_meals_philo_had(t_philo *philo)
{
	int	nbr_meals_had;

	pthread_mutex_lock(&philo->mut_nbr_meals_had);
	nbr_meals_had = philo->nbr_meals_had;
	pthread_mutex_unlock(&philo->mut_nbr_meals_had);
	return (nbr_meals_had);
}

uint64_t	get_start_time(t_data *data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_start_time);
	time = data->start_time;
	pthread_mutex_unlock(&data->mut_start_time);
	return (time);
}
