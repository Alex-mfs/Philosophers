/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/25 10:49:05 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	assign_var(t_minish *ms)
{
	int		i;
	char	*str;

	i = -1;
	if (ms->tk_list->token && ms->tk_list->token[0])
	{
		str = ms->tk_list->token;
		if (str[0] == '='
			|| str[ft_strlen(str) - 1] == '=')
		{
			error("minishell: bad assignment \n", 1);
			return (true);
		}
		while (str[++i])
		{
			if (str[i] == '=')
			{
				add_or_update_env(&ms->env_tmp, str);
				return (true);
			}
		}
	}
	return (false);
}

static void	compute(t_minish *ms, char *input)
{
	if (!validate_quotes(input))
		return ;
	get_tokens(ms, input);
	if (!validate_tokens(ms))
		return ;
	expand(ms);
	parse(ms);
	if (!assign_var(ms))
		execute(ms);
	sanitize_path(ms);
	unlink("heredoc_tmp");
}

static char	*maintain_prompt(char *cwd)
{
	char	*prompt;
	char	*suffix;

	prompt = ft_strdup("\033[1m""\033[34m""Curr.Directory:""\033[0m""\033[34m");
	if (!prompt)
		return (NULL);
	suffix = ft_strdup("\033[0m""\n""\033[4m""\033[97m" \
			"Input minishell:""\033[0m");
	if (!suffix)
	{
		free(prompt);
		return (NULL);
	}
	prompt = ft_strbuild(prompt, cwd);
	if (!prompt)
	{
		free(suffix);
		return (NULL);
	}
	prompt = ft_strbuild(prompt, suffix);
	free(suffix);
	return (prompt);
}

void	read_inputs(t_minish *ms)
{
	char	*prompt;
	char	*input;

	while (1)
	{
		prompt = maintain_prompt(ms->cwd);
		input = readline(prompt);
		free(prompt);
		if (!input)
		{
			ft_error_msg("Input allocation error.\nExiting minishell\n");
			sanitize_ms(ms, true);
			break ;
		}
		add_history(input);
		compute(ms, input);
		free(input);
		sanitize_ms(ms, false);
	}
	rl_clear_history();
}
