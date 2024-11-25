/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_add_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/05 11:57:50 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **tab, int w)
{
	while (tab[w])
	{
		free(tab[w]);
		w++;
	}
	free(tab[w]);
	free(tab);
	return (NULL);
}

static int	countlines(char **src)
{
	int		w;

	w = 0;
	while (src[w])
		w++;
	return (w);
}

char	**ft_matrix_add_line(char **src, char *newline)
{
	char	**dest;
	int		w;

	w = 0;
	if (src)
		w = countlines(src);
	w++;
	dest = ft_calloc(w + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	dest[w] = 0;
	w--;
	dest[w] = ft_strdup(newline);
	free(newline);
	w--;
	while (w >= 0)
	{
		dest[w] = ft_strdup(src[w]);
		if (!dest[w])
			return (free_all(dest, w + 1));
		w--;
	}
	if (src)
		free_all(src, 0);
	return (dest);
}
