/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:07:12 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/16 18:24:06 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_dir(char *path, t_minish *ms)
{
	char	*oldpwd;
	char	*newpwd;

	if (!path)
	{
		error("minishell: cd: HOME not set\n", 1);
		return ;
	}
	oldpwd = ft_strjoin("OLDPWD=", ms->cwd);
	add_or_update_env(&ms->env_list, oldpwd);
	free(oldpwd);
	chdir(path);
	free(ms->cwd);
	ms->cwd = getcwd(NULL, 4096);
	newpwd = ft_strjoin("PWD=", ms->cwd);
	add_or_update_env(&ms->env_list, newpwd);
	free(newpwd);
	free(path);
}

void	cd(char **tokens, t_minish *ms)
{
	struct stat	stats;
	int			i;

	i = 0;
	while (tokens[i])
		i++;
	if (i > 1)
	{
		error("minishell: cd: too many arguments\n", 1);
		return ;
	}
	if (!tokens[0] || ft_str_cmp(tokens[0], "~"))
	{
		change_dir(get_env("HOME", ms->env_list), ms);
		return ;
	}
	if (stat(tokens[0], &stats) == 0 && S_ISDIR(stats.st_mode))
		change_dir(ft_strdup(tokens[0]), ms);
	else
		error("minishell: cd: not a directory\n", 127);
}
