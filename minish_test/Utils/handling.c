/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/28 14:19:54 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_interrupt(int signum)
{
	if (signum != SIGINT)
		return ;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	set_exit_status(130);
}

void	handle_child_quit(int signal)
{
	if (signal != SIGQUIT)
		return ;
	ft_putstr_fd("Quit: 3\n", 2);
	set_exit_status(130);
}

void	handle_child_interrupt(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putstr_fd("\n", 2);
	set_exit_status(131);
}

void	handle_heredoc_interrupt(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		set_exit_status(130);
		exit(130);
	}
}
