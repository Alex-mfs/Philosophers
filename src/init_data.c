/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:25:19 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/30 15:01:52 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_forks(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = data->philos;
	i = -1;
	while (++i < data->philos_nbr)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	philos[0].left_f = &data->forks[0];
	philos[0].right_f = &data->forks[data->philos_nbr - 1];
	while (++i < data->philos_nbr)
	{
		philos[i].left_f = &data->forks[i];
		philos[i].right_f = &data->forks[i - 1];
	}
	return (0);
}

int	init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = data->philos;
	while (i < data->philos_nbr)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].nbr_meals_had = 0;
		philos[i].state = IDLE;
		pthread_mutex_init(&philos[i].mut_state, NULL);
		pthread_mutex_init(&philos[i].mut_nbr_meals_had, NULL);
		pthread_mutex_init(&philos[i].mut_last_time_eaten, NULL);
		update_last_meal_time(&philos[i]);
		i++;
	}
	return (0);
}

int	malloc_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philos_nbr);
	if (data->philos == NULL)
		return (MALLOC_ERROR);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_nbr);
	if (data->forks == NULL)
		return (free(data->philos), MALLOC_ERROR);
	data->philo_ths = malloc(sizeof(pthread_t) * data->philos_nbr);
	if (data->philo_ths == NULL)
		return (free(data->philos), free(data->forks), MALLOC_ERROR);
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->keep_iterating = true;
	data->philos_nbr = ft_atoi(argv[1]);
	data->time2die = (u_int64_t) ft_atoi(argv[2]);
	data->time2eat = (u_int64_t) ft_atoi(argv[3]);
	data->time2sleep = (u_int64_t) ft_atoi(argv[4]);
	data->nbr_meals = -1;
	if (argc == 6)
		data->nbr_meals = ft_atoi(argv[5]);
	pthread_mutex_init(&data->mut_eat_t, NULL);
	pthread_mutex_init(&data->mut_sleep_t, NULL);
	pthread_mutex_init(&data->mut_die_t, NULL);
	pthread_mutex_init(&data->mut_print, NULL);
	pthread_mutex_init(&data->mut_philos_nbr, NULL);
	pthread_mutex_init(&data->mut_keep_iter, NULL);
	pthread_mutex_init(&data->mut_start_time, NULL);
	return (malloc_data(data));
}
