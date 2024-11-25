/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_export_aux_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:29:37 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/23 01:07:59 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strlen_sep(const char *s, char *seps)
{
	int	i;

	i = 0;
	while (s[i] && !ft_strchr(seps, s[i]))
		i++;
	return (i);
}

int	find_env_in_tmp(t_minish *ms, const char *name)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (ms->env_tmp[i])
	{
		if (!ft_strncmp(ms->env_tmp[i], name, len) && \
		ms->env_tmp[i][len] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*extract_key(const char *assignment)
{
	size_t	len;
	char	*key;

	len = ft_strlen_sep(assignment, "=");
	key = ft_substr(assignment, 0, len);
	return (key);
}

void	copy_env_except_key(char **src, char **dest, const char *key, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (!(ft_strncmp(src[i], key, len) == 0 && src[i][len] == '='))
		{
			dest[j] = src[i];
			j++;
		}
		else
		{
			free(src[i]);
		}
		i++;
	}
	dest[j] = NULL;
}

void	remove_from_tmp(t_minish *ms, const char *key)
{
	int		i;
	int		len;
	char	**new_env_tmp;

	len = ft_strlen(key);
	i = 0;
	while (ms->env_tmp[i])
		i++;
	new_env_tmp = malloc(sizeof(char *) * i);
	if (!new_env_tmp)
		return ;
	copy_env_except_key(ms->env_tmp, new_env_tmp, key, len);
	free(ms->env_tmp);
	ms->env_tmp = new_env_tmp;
}
