/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_repl_seg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/05 11:49:21 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*replace_short(const char *str, char *old, char *new, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	b;
	char	*str2;

	i = 0;
	j = 0;
	b = ft_strnstr_pos(str, old, len);
	str2 = ft_calloc(len - ft_strlen(old) + ft_strlen(new), sizeof(char *));
	if (!str2)
		return (NULL);
	while (i <= len)
	{
		if (i == b)
		{
			j = ft_strlen(new);
			ft_memcpy(&str2[i], new, j);
			b = ft_strlen(old);
			i += b;
			j = b - j;
		}
		str2[i - j] = str[i];
		i++;
	}
	return (str2);
}

static char	*replace_long(const char *str, char *old, char *new, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	b;
	char	*str2;

	i = 0;
	j = 0;
	b = ft_strnstr_pos(str, old, len);
	str2 = ft_calloc(len - ft_strlen(old) + ft_strlen(new), sizeof(char *));
	if (!str2)
		return (NULL);
	while (i <= len)
	{
		if (i == b)
		{
			j = ft_strlen(new);
			ft_memcpy(&str2[i], new, j);
			b = ft_strlen(old);
			i += b;
			j -= b;
		}
		str2[i + j] = str[i];
		i++;
	}
	return (str2);
}

char	*ft_str_repl_seg(const char *str, char *old, char *new)
{
	size_t	len;
	size_t	o;
	size_t	n;
	char	*str2;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	o = ft_strlen(old);
	n = ft_strlen(new);
	if (!old || o > len || !ft_strnstr(str, old, len))
		return (NULL);
	if (n > o)
		str2 = replace_long(str, old, new, len);
	else
		str2 = replace_short(str, old, new, len);
	return (str2);
}
