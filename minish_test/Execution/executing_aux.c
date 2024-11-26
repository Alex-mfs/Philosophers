/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:46:55 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/26 19:11:40 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	need2be_parent(char *command, char *arg, t_minish *ms)
{
	bool	is_parent;

	is_parent = false;
	if (ms->qtd_pipes > 0)
	{
		ms->qtd_pipes--;
		return (false);
	}
	if (ft_str_cmp(command, "cd") == true)
		is_parent = true;
	else if (ft_str_cmp(command, "exit") == true)
		is_parent = true;
	else if (ft_str_cmp(command, "export") == true && arg != NULL)
		is_parent = true;
	else if (ft_str_cmp(command, "unset") == true)
		is_parent = true;
	return (is_parent);
}

bool	is_redirection(char *cmd)
{
	if (ft_strchr(cmd, '<') || ft_strchr(cmd, '>'))
		return (true);
	return (false);
}

bool	is_redir_or_pipe(char *cmd)
{
	if (ft_strchr(cmd, '|') || is_redirection(cmd))
		return (true);
	return (false);
}

void	error(char *str, int status)
{
	//printf("%s", str);
	printf("error: %s, setting exit status to %d\n", str, status);
	set_exit_status(status);
}
