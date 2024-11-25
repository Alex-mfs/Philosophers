/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:18:12 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/24 16:07:15 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_export(t_minish *ms)
{
	int		i;
	char	*equals_sign;

	i = 0;
	while (ms->env_list[i])
	{
		equals_sign = ft_strchr(ms->env_list[i], '=');
		if (equals_sign)
			printf("declare -x %s\n", ms->env_list[i]);
		else
			printf("declare -x %s=\"\"\n", ms->env_list[i]);
		i++;
	}
}

void	add_or_update_env(char ***target_env, const char *assignment)
{
	int		index;

	index = find_env_index(*target_env, assignment);
	if (index != -1)
	{
		free((*target_env)[index]);
		(*target_env)[index] = ft_strdup(assignment);
	}
	else
		add_new_env(target_env, assignment);
}

void	handle_no_assignment(t_minish *ms, char *arg)
{
	char	*new_assign;
	char	*env_value_tmp;
	size_t	assign_len;
	int		index;

	env_value_tmp = NULL;
	index = find_env_index(ms->env_tmp, arg);
	if (index != -1)
		env_value_tmp = ft_strchr(ms->env_tmp[index], '=');
	assign_len = ft_strlen(arg) + 2;
	if (env_value_tmp)
		assign_len += ft_strlen(env_value_tmp + 1);
	new_assign = malloc(assign_len);
	if (!new_assign)
		return ;
	ft_strlcpy(new_assign, arg, ft_strlen(arg) + 1);
	ft_strlcat(new_assign, "=", ft_strlen(arg) + 2);
	if (env_value_tmp)
		ft_strlcat(new_assign, env_value_tmp + 1, assign_len);
	add_or_update_env(&ms->env_list, new_assign);
	free(new_assign);
	add_or_update_env(&ms->env_tmp, arg);
}

void	handle_assignment(t_minish *ms, char *arg)
{
	char	*key;

	key = extract_key(arg);
	if (find_env_index(ms->env_tmp, key) != -1)
		remove_from_tmp(ms, key);
	free(key);
	add_or_update_env(&ms->env_list, arg);
	add_or_update_env(&ms->env_tmp, arg);
}

void	ft_export(char **exp_args, t_minish *ms)
{
	int	i;

	i = 0;
	if (!exp_args[0])
		print_export(ms);
	while (exp_args[i])
	{
		if (ft_strchr(exp_args[i], '='))
			handle_assignment(ms, exp_args[i]);
		else
			handle_no_assignment(ms, exp_args[i]);
		i++;
	}
}
