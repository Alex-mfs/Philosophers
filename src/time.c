/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:26:08 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/30 14:56:41 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	wait_until(u_int64_t wakeup_time)
{
	int			margin;
	u_int64_t	time;

	margin = 5;
	while (1)
	{
		time = get_time();
		if (wakeup_time <= time + margin)
		{
			while (wakeup_time > time)
				time = get_time();
			break ;
		}
		else
		{
			usleep(1000 * (wakeup_time - time - margin));
		}
	}
}

void	ft_usleep(uint64_t time2sleep)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time2sleep)
		usleep(500);
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}
