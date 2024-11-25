/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2023/07/23 17:54:04 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include "ft_printf.h"

int	ft_putnbr_fd(long n, int fd)
{
	long	nb;
	char	c;
	int		l;

	nb = n;
	l = 1;
	if (n < 0)
	{
		l += write(fd, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
	{
		l += ft_putnbr_fd(nb / 10, fd);
		nb %= 10;
	}
	c = nb + '0';
	write(fd, &c, 1);
	return (l);
}
