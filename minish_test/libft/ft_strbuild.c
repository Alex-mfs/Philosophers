/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbuild.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/05 11:28:04 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strbuild(char *s1, const char *s2)
{
	char	*joined;
	size_t	l;
	size_t	l1;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (s1);
	l1 = ft_strlen(s1);
	l = l1 + ft_strlen(s2) + 1;
	joined = malloc(l * sizeof(char));
	if (!joined)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(joined, s1, l);
	ft_strlcat(joined, s2, l);
	free(s1);
	return (joined);
}
