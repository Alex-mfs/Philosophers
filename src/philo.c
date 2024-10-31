/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:25:39 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/30 14:44:29 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	run_threads(t_data *data)
{
	int	i;
	int	nb_of_philos;

	nb_of_philos = get_philos_nbr(data);
	i = -1;
	data->start_time = get_time();
	while (++i < nb_of_philos)
	{
		if (pthread_create(&data->philo_ths[i], NULL,
				&routine, &data->philos[i]))
			return (1);
	}
	if (pthread_create(&data->monit_all_alive, NULL,
			&all_alive_routine, data))
		return (1);
	if (nbr_meals_option(data) == true
		&& pthread_create(&data->monit_all_full, NULL,
			&all_full_routine, data))
		return (1);
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;
	int	philos_nbr;

	philos_nbr = get_philos_nbr(data);
	i = -1;
	if (pthread_join(data->monit_all_alive, NULL))
		return (1);
	if (nbr_meals_option(data) == true
		&& pthread_join(data->monit_all_full, NULL))
		return (1);
	while (++i < philos_nbr)
	{
		if (pthread_join(data->philo_ths[i], NULL))
			return (1);
	}
	return (0);
}

int	philosophers(int argc, char **argv)
{
	t_data	data;

	if (init_data(&data, argc, argv) != 0)
		return (MALLOC_ERROR);
	init_philos(&data);
	init_forks(&data);
	run_threads(&data);
	join_threads(&data);
	free_data(&data);
	return (0);
}

void	leaks(void)
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	if (check_input(argc, argv) != 0)
	{
		print_instruction();
		return (WRONG_INPUT);
	}
	if (philosophers(argc, argv) != 0)
		return (MALLOC_ERROR);
	return (0);
}
