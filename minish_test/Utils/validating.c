/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/06 16:22:07 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	validation_error(char *msg)
{
	printf("\033[1m""\033[31m""""Error: ""\033[0m""%s\n", msg);
	set_exit_status(2);
	return (false);
}

static int	find_match(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == quote)
			return (i + 1);
		i++;
	}
	return (0);
}

bool	validate_quotes(char *input)
{
	int		i;
	int		check;

	i = 0;
	while (input[i])
	{
		check = i;
		if (input[i] == '\"' || input[i] == '\'')
		{
			i += find_match(input + i, input[i]);
			if (i == check)
				return (validation_error("Unclosed quotes"));
		}
		else
			i++;
	}
	return (true);
}

static bool	tk_red_pip(t_token *tk)
{
	if (tk->type >= REDIR_INPUT_1 && tk->type <= PIPE)
		return (true);
	return (false);
}

bool	validate_tokens(t_minish *ms)
{
	t_token	*curr;

	curr = ms->tk_list;
	if (curr->type == PIPE)
		return (validation_error("Input syntax near pipe"));
	while (curr)
	{
		if ((curr->type >= REDIR_INPUT_1 && curr->type <= REDIR_OUTPUT_2)
			&& (!curr->next || tk_red_pip(curr->next)))
			return (validation_error("Input syntax near redirection"));
		if (curr->type == PIPE
			&& (!curr->next || curr->next->type == PIPE))
			return (validation_error("Unclosed pipe"));
		curr = curr->next;
	}
	return (true);
}
