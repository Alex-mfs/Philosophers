/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/05/03 11:12:47 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	water_near(char **tab, t_point pos, t_point size)
{
	if (pos.y != 0 && tab[pos.y - 1][pos.x] == 'F')
		return (1);
	if (pos.y != (size.y - 1) && tab[pos.y + 1][pos.x] == 'F')
		return (1);
	if (pos.x != 0 && tab[pos.y][pos.x - 1] == 'F')
		return (1);
	if (pos.x != (size.x - 1) && tab[pos.y][pos.x + 1] == 'F')
		return (1);
	return (0);
}

static int	check_flood(char **tab, t_point pos, t_point size, char drown)
{
	if (tab[pos.y][pos.x] == drown && water_near(tab, pos, size))
	{
		tab[pos.y][pos.x] = 'F';
		return (1);
	}
	return (0);
}

void	flood_fill(char **tab, t_point size, t_point begin)
{
	char	drown;
	int		progress;
	t_point	pos;

	drown = tab[begin.y][begin.x];
	tab[begin.y][begin.x] = 'F';
	progress = 1;
	while (progress)
	{
		progress = 0;
		pos.y = 0;
		while (pos.y < size.y)
		{
			pos.x = 0;
			while (pos.x < size.x)
			{
				progress += check_flood(tab, pos, size, drown);
				pos.x++;
			}
			pos.y++;
		}
	}
}
