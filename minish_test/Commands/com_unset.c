/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:54:07 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/28 14:16:02 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_var_from_env(char ***env_list, const char *key)
{
	int		i;
	int		len;
	char	**new_env_list;

	len = ft_strlen(key);
	i = 0;
	while ((*env_list)[i])
		i++;
	new_env_list = malloc(sizeof(char *) * i);
	if (!new_env_list)
		return ;
	copy_env_except_key(*env_list, new_env_list, key, len);
	free(*env_list);
	*env_list = new_env_list;
}

void	unset(char **vars, t_minish *ms)
{
	int	i;

	i = 0;
	while (vars[i])
	{
		remove_var_from_env(&ms->env_list, vars[i]);
		remove_var_from_env(&ms->env_tmp, vars[i]);
		i++;
	}
}
