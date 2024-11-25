/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_export_aux_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:32:47 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/23 01:53:23 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_new_env(char ***target_env, const char *assignment)
{
	int		i;
	char	**new_env_list;
	int		j;

	i = 0;
	j = 0;
	while ((*target_env)[i])
		i++;
	new_env_list = malloc(sizeof(char *) * (i + 2));
	if (!new_env_list)
		return ;
	while (j < i)
	{
		new_env_list[j] = (*target_env)[j];
		j++;
	}
	new_env_list[i] = ft_strdup(assignment);
	new_env_list[i + 1] = NULL;
	free(*target_env);
	*target_env = new_env_list;
}

int	find_env_index(char **target_env, const char *assigment)
{
	int		i;
	size_t	len;
	char	*key;

	key = ft_substr(assigment, 0, ft_strlen_sep(assigment, "="));
	len = ft_strlen(key);
	i = 0;
	while (target_env[i])
	{
		if (ft_strncmp(target_env[i], key, len) == 0 && \
		target_env[i][len] == '=')
		{
			free(key);
			return (i);
		}
		i++;
	}
	free(key);
	return (-1);
}
