/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2023/07/30 15:47:19 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	d;
	size_t	l;

	i = 0;
	d = ft_strlen(dest);
	if (size < d)
		l = ft_strlen(src) + size;
	else
		l = ft_strlen(src) + d;
	while ((d + 1) < size && src[i] != '\0')
	{
		dest[d] = src[i];
		i++;
		d++;
	}
	dest[d] = '\0';
	return (l);
}
