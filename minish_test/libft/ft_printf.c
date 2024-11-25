/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:29:54 by joao-rib          #+#    #+#             */
/*   Updated: 2023/10/24 17:30:10 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include "ft_printf.h"
//#include <stdio.h>

static int	prf_ptr(unsigned long v)
{
	int	l;

	if (!v)
		l = write(1, "(nil)", 5);
	else
	{
		l = write(1, "0x", 2);
		l += ft_putnbr_lbase_fd(v, HEXA_LOW, 1);
	}
	return (l);
}

static int	check_format(const char c, va_list args)
{
	int	p;

	p = -2;
	if (c == 'd' || c == 'i')
		p += ft_putnbr_fd((long)va_arg(args, int), 1);
	else if (c == 'u')
		p += ft_putnbr_ubase_fd(va_arg(args, unsigned int), DECIMAL, 1);
	else if (c == 'x')
		p += ft_putnbr_ubase_fd(va_arg(args, unsigned int), HEXA_LOW, 1);
	else if (c == 'X')
		p += ft_putnbr_ubase_fd(va_arg(args, unsigned int), HEXA_UPP, 1);
	else if (c == 'c')
		p += ft_putchar_fd(va_arg(args, int), 1);
	else if (c == 's')
		p += ft_putstr_fd(va_arg(args, char *), 1);
	else if (c == 'p')
		p += prf_ptr(va_arg(args, unsigned long));
	else
		p += ft_putchar_fd(c, 1);
	return (p);
}

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		i;
	int		p;

	va_start(args, string);
	i = 0;
	p = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			i++;
			if (ft_strchr(CONVERSION, string[i]))
				p += check_format(string[i], args);
			else
				ft_putchar_fd(string[i], 1);
		}
		else
			ft_putchar_fd(string[i], 1);
		i++;
	}
	va_end(args);
	return (i + p);
}

/*int	main(void)
{
	printf("Return: %d\n", printf("\nOriginal printf:\n"));
	printf("Return: %d\n", printf("CHAR %c CHAR\n", 'd'));
	printf("Return: %d\n", printf("STRING %s STRING\n", "null"));
	printf("Return: %d\n", printf("POINTER %p POINTER\n", &"hi"));
	printf("Return: %d\n", printf("DECIMAL %d DECIMAL\n", 23));
	printf("Return: %d\n", printf("INTEGER %i INTEGER\n", 42));
	printf("Return: %d\n", printf("UNS DECIMAL %u UNS DECIMAL\n", -81));
	printf("Return: %d\n", printf("hexadec %x hexadec\n", 42));
	printf("Return: %d\n", printf("HEXADEC %X HEXADEC\n", 42));
	printf("Return: %d\n", printf("PERCENT %% PERCENT\n"));
	ft_printf("Return: %d\n", ft_printf("\nft_printf:\n"));
	ft_printf("Return: %d\n", ft_printf("CHAR %c CHAR\n", 'd'));
	ft_printf("Return: %d\n", ft_printf("STRING %s STRING\n", "null"));
	ft_printf("Return: %d\n", ft_printf("POINTER %p POINTER\n", &"hi"));
	ft_printf("Return: %d\n", ft_printf("DECIMAL %d DECIMAL\n", 23));
	ft_printf("Return: %d\n", ft_printf("INTEGER %i INTEGER\n", 42));
	ft_printf("Return: %d\n", ft_printf("UNS DECIMAL %u UNS DECIMAL\n", -81));
	ft_printf("Return: %d\n", ft_printf("hexadec %x hexadec\n", 42));
	ft_printf("Return: %d\n", ft_printf("HEXADEC %X HEXADEC\n", 42));
	ft_printf("Return: %d\n", ft_printf("PERCENT %% PERCENT\n"));
	return (0);
}*/

/*int	main(void)
{
	ft_printf("\nft_printf:\n");
	ft_printf(" count: %i\n", ft_printf("NULL %s NULL", 0));
	ft_printf("\t count: %i\n", ft_printf("%d", 2147483647));
	ft_printf("\t\t count: %d\n", ft_printf("%i", -101));
	ft_printf("\t count: %i\n", ft_printf("%i", -2147483648));
	ft_printf("\t count: %i\n", ft_printf("%u", 4294967295));
	ft_printf("\t\t count: %i\n", ft_printf("%x", 255));
	ft_printf("\t count: %i\n", ft_printf("%X", -2147483648));
	ft_printf("\t count: %i\n", ft_printf("%p", &"hi"));
	ft_printf("\t\t count: %i\n", ft_printf("%p", 0));
	printf("\nprintf:\n");
	printf(" count: %i\n", printf("NULL %s NULL", (char *) 0));
	printf("\t count: %i\n", printf("%i", 2147483647));
	printf("\t\t count: %d\n", printf("%i", -101));
	printf("\t count: %i\n", printf("%li", -2147483648));
	printf("\t count: %i\n", printf("%ld", 4294967295));
	printf("\t\t count: %i\n", printf("%x", 255));
	printf("\t count: %i\n", printf("%X", (unsigned int)-2147483648));
	printf("\t count: %i\n", printf("%p", &"hi"));
	printf("\t\t count: %i\n", printf("%p", (void *) 0));
	return (0);
}*/
