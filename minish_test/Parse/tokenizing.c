/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/25 09:36:34 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	is_tk_delim(int c)
{
	if (c == ' ' || c == '<' || c == '>'
		|| c == '|' || c == '\'' || c == '\"'
		|| c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (true);
	else
		return (false);
}

static int	save_token(t_minish *ms, char *symbol, t_lexer type, bool merge)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		ft_error_msg("Error while creating token");
	token->token = ft_strdup(symbol);
	if (!token->token)
		ft_error_msg("Error while saving token");
	token->type = type;
	token->next = NULL;
	token->to_merge = merge;
	if (!merge)
		ms->aux_merge = false;
	tklst_addback(&ms->tk_list, token);
	return ((int)ft_strlen(symbol));
}

static int	quote_limit(char *str, char limit)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != limit)
		i++;
	if (str[i] == '\0')
		return (0);
	return (i);
}

static int	save_cmd(t_minish *ms, char *input, char limit)
{
	int		i;
	char	*content;

	i = 0;
	if (limit == ' ')
	{
		while (input[i] && !is_tk_delim(input[i]))
			i++;
	}
	else
		i = quote_limit(input, limit);
	content = ft_substr(input, 0, i);
	if (!content)
		ft_error_msg("Token memory allocation");
	if (limit == '\"')
		save_token(ms, content, DOUBLE_QUOTES, ms->aux_merge);
	else if (limit == '\'')
		save_token(ms, content, SINGLE_QUOTES, ms->aux_merge);
	else
		save_token(ms, content, OTHER, ms->aux_merge);
	free(content);
	ms->aux_merge = true;
	return (i);
}

void	get_tokens(t_minish *ms, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_isdelim(input[i]) && i++ >= 0)
			ms->aux_merge = false;
		else if (input[i] == '|')
			i += save_token(ms, "|", PIPE, false);
		else if (input[i] == '<' && input[i + 1] == '<')
			i += save_token(ms, "<<", REDIR_INPUT_2, false);
		else if (input[i] == '>' && input[i + 1] == '>')
			i += save_token(ms, ">>", REDIR_OUTPUT_2, false);
		else if (input[i] == '<')
			i += save_token(ms, "<", REDIR_INPUT_1, false);
		else if (input[i] == '>')
			i += save_token(ms, ">", REDIR_OUTPUT_1, false);
		else if (input[i] == '\"')
			i += 2 + save_cmd(ms, &input[i + 1], '\"');
		else if (input[i] == '\'')
			i += 2 + save_cmd(ms, &input[i + 1], '\'');
		else
			i += save_cmd(ms, &input[i], ' ');
	}
}
