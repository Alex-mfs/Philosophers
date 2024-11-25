/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:19:22 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/25 11:04:13 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*skip_whitespace(char *str)
{
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	return (str);
}

long long	ft_atoll(char *str)
{
	unsigned long long	num;
	int					sign;

	num = 0;
	sign = 1;
	str = skip_whitespace(str);
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (*str < '0' || *str > '9')
		return (255);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str++ - '0');
		if ((sign > 0 && num > (unsigned long long)LLONG_MAX) || \
			(sign < 0 && num > (unsigned long long)-(LLONG_MIN)))
			return (255);
	}
	if (*str)
		return (255);
	return ((long long)(num * sign));
}

long long	validate_and_convert_arg(char *arg, t_minish *ms)
{
	long long	num;

	num = ft_atoll(arg);
	if (num == 255)
	{
		error("exit: numeric argument required\n", 255);
		sanitize_ms(ms, true);
	}
	return (num);
}

long long	calculate_exit_code(long long num)
{
	num = num % 256;
	if (num < 0)
		num += 256;
	return (num);
}

void	exit_bash(char **exit_args, t_minish *ms)
{
	size_t		arg_num;
	long long	num;

	arg_num = 0;
	num = 0;
	while (exit_args[arg_num] && exit_args[arg_num][0])
		arg_num++;
	if (arg_num > 1)
	{
		error("exit: too many arguments\n", 1);
		return ;
	}
	if (arg_num == 1)
	{
		num = validate_and_convert_arg(exit_args[0], ms);
		num = calculate_exit_code(num);
		set_exit_status(num);
	}
	if (arg_num == 0)
		set_exit_status(0);
	printf("exit\n");
	sanitize_ms(ms, true);
}
