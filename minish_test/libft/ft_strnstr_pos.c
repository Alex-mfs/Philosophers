/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2023/07/30 13:37:33 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnstr_pos(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	b;

	i = 0;
	if (little[0] == '\0')
		return (0);
	while (i <= len && big[i] != '\0')
	{
		b = i;
		j = 0;
		while (big[i] == little[j] && little[j] != '\0')
		{
			i++;
			j++;
		}
		if (i > len)
			return (0);
		if (little[j] == '\0')
			return (b);
		i = b + 1;
	}
	return (0);
}
