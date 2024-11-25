/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2023/07/28 11:29:50 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t		i;
	size_t		l;

	i = 0;
	if (size > 0)
	{
		while (i < size && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
	}
	if (i == size && i != 0)
		i--;
	if (size > 0)
		dest[i] = '\0';
	l = 0;
	while (src[l] != '\0')
		l++;
	return (l);
}
