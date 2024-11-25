/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_repl_chr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/19 17:52:36 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_repl_chr(char *str, char old, char new, size_t times)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!str)
		return (NULL);
	if (times == 0)
		return (str);
	len = ft_strlen(str);
	while (i <= len)
	{
		if (str[i] == old)
		{
			str[i] = new;
			times--;
			if (times == 0)
				break ;
		}
		i++;
	}
	return (str);
}
