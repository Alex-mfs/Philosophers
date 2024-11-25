/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialising.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/25 11:35:31 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*increment_string(char *num)
{
	int	nbr;

	if (!num)
		return (NULL);
	nbr = ft_atoi(num);
	nbr++;
	free(num);
	return (ft_itoa(nbr));
}

void	init_ms(t_minish *ms, char **envp)
{
	char	*path_env;
	char	*shlvl;
	char	*buff;

	ms->env_list = ft_matrix_dup(envp);
	ms->env_tmp = ft_matrix_dup(envp);
	buff = get_env("SHLVL", envp);
	buff = increment_string(buff);
	shlvl = ft_strjoin("SHLVL=", buff);
	free(buff);
	add_or_update_env(&ms->env_list, shlvl);
	add_or_update_env(&ms->env_tmp, shlvl);
	free(shlvl);
	ms->cmd_list = NULL;
	ms->cwd = getcwd(NULL, 4096);
	ms->fd_in = 0;
	ms->fd_out = 1;
	path_env = getenv("PATH");
	if (path_env)
		ms->path = ft_split(path_env, ':');
	else
		ms->path = NULL;
	ms->aux_merge = false;
}
