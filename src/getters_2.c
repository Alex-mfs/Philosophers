/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:25:10 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/31 15:44:17 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

uint64_t	get_time2die(t_data *data)
{
	uint64_t	time2die;

	pthread_mutex_lock(&data->mut_die_t);
	time2die = data->time2die;
	pthread_mutex_unlock(&data->mut_die_t);
	return (time2die);
}

uint64_t	get_time2sleep(t_data *data)
{
	uint64_t	time2sleep;

	pthread_mutex_lock(&data->mut_sleep_t);
	time2sleep = data->time2sleep;
	pthread_mutex_unlock(&data->mut_sleep_t);
	return (time2sleep);
}

uint64_t	get_time2eat(t_data *data)
{
	uint64_t	time2eat;

	pthread_mutex_lock(&data->mut_eat_t);
	time2eat = data->time2eat;
	pthread_mutex_unlock(&data->mut_eat_t);
	return (time2eat);
}

uint64_t	get_last_time_eaten(t_philo *philo)
{
	uint64_t	last_time_eaten;

	pthread_mutex_lock(&philo->mut_last_time_eaten);
	last_time_eaten = philo->last_time_eaten;
	pthread_mutex_unlock(&philo->mut_last_time_eaten);
	return (last_time_eaten);
}
