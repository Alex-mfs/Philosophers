/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2023/07/31 22:32:21 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include "ft_printf.h"

static int	repeat_chars(char *str, char t)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == t)
			count++;
		i++;
	}
	if (count <= 1)
		return (0);
	else
		return (1);
}

static int	check_valid(char *str, int b)
{
	int	i;

	i = 0;
	if (b <= 1)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] <= 32 || str[i] == 127)
			return (0);
		else if (str[i] == '-' || str[i] == '+')
			return (0);
		else if (repeat_chars(str, str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_putnbr_lbase_fd(unsigned long nbr, char *base, int fd)
{
	unsigned long	b;
	int				l;

	b = 0;
	l = 1;
	while (base[b] != '\0')
		b++;
	if (!check_valid(base, b))
		return (0);
	if (nbr >= b)
	{
		l += ft_putnbr_lbase_fd(nbr / b, base, fd);
		nbr %= b;
	}
	write(1, &base[nbr], fd);
	return (l);
}
