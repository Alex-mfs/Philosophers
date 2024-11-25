/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/05/07 17:27:19 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	int		countmin;
	long	r;

	i = 0;
	r = 0;
	countmin = 0;
	while (ft_whitespace(str[i]) && str[i] != '\0')
		i++;
	if (str[i] == '-')
	{
		countmin++;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		r = r * 10;
		r += str[i] - 48;
		i++;
	}
	if (countmin)
		r = r * -1;
	return (r);
}
