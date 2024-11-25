/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:21:00 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/28 14:17:15 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env(const char *key, char **env_list)
{
	int		i;
	size_t	key_len;
	char	*env_key;

	i = 0;
	if (key[0] == '$')
		key++;
	key_len = ft_strlen(key);
	while (env_list[i])
	{
		env_key = env_list[i];
		if (ft_strncmp(env_key, key, key_len) == 0 && env_key[key_len] == '=')
			return (ft_strdup(env_key + key_len + 1));
		i++;
	}
	return (ft_strdup(""));
}

void	env(char **env_arg, char **env_list)
{
	int	i;

	i = 0;
	if (env_arg[1] != NULL)
	{
		error("env: no such file or directory: \n", 127);
		return ;
	}
	while (env_list[i])
	{
		printf("%s\n", env_list[i]);
		i++;
	}
}
