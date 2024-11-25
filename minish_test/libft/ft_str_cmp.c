/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/05/07 17:29:13 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_str_cmp(const char *s1, const char *s2)
{
	size_t	i;
	int		r;

	i = 0;
	r = 0;
	while (s1[i] != '\0' && r == 0)
	{
		r = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (r != 0)
			return (false);
		i++;
	}
	if (r == 0 && ft_strlen(s1) < ft_strlen(s2))
	{
		while (s2[i] != '\0')
		{
			r -= (unsigned char)s2[i];
			if (r != 0)
				return (false);
			i++;
		}
	}
	return (true);
}
