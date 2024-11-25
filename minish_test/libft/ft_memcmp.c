/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2023/07/29 20:53:17 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*ptr1;
	const char	*ptr2;
	size_t		i;
	int			r;

	i = 0;
	r = 0;
	ptr1 = s1;
	ptr2 = s2;
	while (i < n && r == 0)
	{
		r = (unsigned char)ptr1[i] - (unsigned char)ptr2[i];
		i++;
	}
	if (r > 0)
		r /= r;
	else if (r < 0)
		r /= -r;
	return (r);
}
