/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2023/08/05 16:57:01 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *str, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dest;

	i = 0;
	if (!str || !f)
		return (NULL);
	dest = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!dest)
		return (NULL);
	while (str[i] != '\0')
	{
		dest[i] = f(i, str[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
