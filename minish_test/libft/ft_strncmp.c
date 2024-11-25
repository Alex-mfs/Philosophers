/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2023/07/29 20:53:17 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		r;

	i = 0;
	r = 0;
	while (s1[i] != '\0' && i < n && r == 0)
	{
		r = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	if (r == 0 && ft_strlen(s1) < ft_strlen(s2) && i < n)
	{
		while (s2[i] != '\0' && i < n)
		{
			r -= (unsigned char)s2[i];
			i++;
		}
	}
	if (r > 0)
		r /= r;
	else if (r < 0)
		r /= -r;
	return (r);
}
