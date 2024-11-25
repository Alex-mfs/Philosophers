/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:56:02 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/25 13:02:15 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_builtin(char *command)
{
	return (!ft_strncmp(command, "exit", ft_strlen(command)) || \
	!ft_strncmp(command, "pwd", ft_strlen(command)) || \
	!ft_strncmp(command, "env", ft_strlen(command)) || \
	!ft_strncmp(command, "echo", ft_strlen(command)) || \
	!ft_strncmp(command, "unset", ft_strlen(command)) || \
	!ft_strncmp(command, "export", ft_strlen(command)) || \
	!ft_strncmp(command, "cd", ft_strlen(command)));
}

char	**join_cmd_arg(char	*cmd, char **args)
{
	int		i;
	int		args_count;
	char	**full_cmd;

	args_count = 0;
	while (args[args_count] && args[args_count][0])
		args_count++;
	full_cmd = malloc(sizeof(char *) * (args_count + 2));
	if (!full_cmd)
		return (NULL);
	full_cmd[0] = ft_strdup(cmd);
	i = 0;
	while (i < args_count)
	{
		full_cmd[i + 1] = ft_strdup(args[i]);
		i++;
	}
	full_cmd[i + 1] = NULL;
	return (full_cmd);
}
