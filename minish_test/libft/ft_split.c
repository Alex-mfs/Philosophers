/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2023/08/06 16:09:47 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **tab, int w)
{
	while (w >= 0)
	{
		free(tab[w]);
		w--;
	}
	free(tab);
	return (NULL);
}

static int	ft_wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	countwords(const char *str, char delim)
{
	size_t	i;
	size_t	w;

	i = 1;
	w = 0;
	if (str[0] == '\0')
		return (0);
	if (str[0] != delim)
		w++;
	while (str[i] != '\0')
	{
		if (str[i] != delim && str[i - 1] == delim)
			w++;
		i++;
	}
	return (w);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = (char **)ft_calloc((countwords(s, c) + 1), sizeof(char *));
	if (!s || !tab)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[j] = ft_substr(s, i, ft_wordlen(&s[i], c));
			if (!tab[j])
				return (free_all(tab, j));
			j++;
			i += ft_wordlen(&s[i], c);
		}
		else
			i++;
	}
	tab[j] = 0;
	return (tab);
}
