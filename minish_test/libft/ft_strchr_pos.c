/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/02 17:15:21 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_pos(const char *str, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!str)
		return (-1);
	len = ft_strlen(str);
	while (i <= len || (unsigned char)c == '\0')
	{
		if (str[i] == c)
			return ((int)i);
		i++;
	}
	return (-1);
}
