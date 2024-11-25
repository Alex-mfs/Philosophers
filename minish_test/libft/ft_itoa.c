/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2023/08/06 16:09:47 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_string(char *empstr, int l, int n)
{
	long	num;

	num = (long)n;
	empstr[l] = '\0';
	l--;
	if (num < 0)
	{
		empstr[0] = '-';
		num *= -1;
	}
	while (num >= 10)
	{
		empstr[l] = (num % 10) + '0';
		num /= 10;
		l--;
	}
	empstr[l] = num + '0';
}

char	*ft_itoa(int n)
{
	char	*final_num;
	size_t	count;
	long	c;

	count = 2;
	c = (long)n;
	if (n < 0)
	{
		c *= -1;
		count++;
	}
	while (c >= 10)
	{
		c /= 10;
		count++;
	}
	final_num = ft_calloc(count, sizeof(char));
	if (!final_num)
		return (NULL);
	fill_string(final_num, count - 1, n);
	return (final_num);
}
