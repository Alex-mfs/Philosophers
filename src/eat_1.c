/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:50:36 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/30 15:01:52 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_last_time_eaten);
	philo->last_time2eat = get_time();
	pthread_mutex_unlock(&philo->mut_last_time_eaten);
}

void	update_nbr_meals_had(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_nbr_meals_had);
	philo->nbr_meals_had++;
	pthread_mutex_unlock(&philo->mut_nbr_meals_had);
}

void	sleep_for_eating(t_philo *philo)
{
	ft_usleep(get_time2eat(philo->data));
}

int	eat(t_philo *philo)
{
	if (take_forks(philo) != 0)
		return (1);
	set_philo_state(philo, EATING);
	print_msg(philo->data, philo->id, EAT);
	update_last_meal_time(philo);
	sleep_for_eating(philo);
	update_nbr_meals_had(philo);
	drop_forks(philo);
	return (0);
}
