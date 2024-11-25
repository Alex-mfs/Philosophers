/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2023/07/30 13:37:33 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	trimleft(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	a;

	i = 0;
	while (s1[i] != '\0' && set[0])
	{
		a = 0;
		j = 0;
		while (set[j] != 0)
		{
			if (s1[i] == set[j])
				a++;
			j++;
		}
		if (a == 0)
			return (i);
		i++;
	}
	return (i);
}

static size_t	trimright(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	a;

	i = ft_strlen(s1) - 1;
	while (i > 0 && set[0])
	{
		a = 0;
		j = 0;
		while (set[j] != 0)
		{
			if (s1[i] == set[j])
				a++;
			j++;
		}
		if (a == 0)
			return (i);
		i--;
	}
	return (i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*dest;
	size_t	start;
	size_t	end;

	start = trimleft(s1, set);
	end = trimright(s1, set);
	if (start > end)
	{
		dest = (char *)malloc(1);
		if (!dest)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	dest = (char *)ft_calloc(end - start + 2, sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s1[start], end - start + 2);
	return (dest);
}
