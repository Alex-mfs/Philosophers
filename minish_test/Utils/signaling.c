/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/25 11:50:32 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_signals(void)
{
	signal(SIGINT, handle_interrupt);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_heredoc_interrupt;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	treat_child_signal(void)
{
	signal(SIGQUIT, handle_child_quit);
	signal(SIGINT, handle_child_interrupt);
}
