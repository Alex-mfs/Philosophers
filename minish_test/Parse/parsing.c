/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/25 20:44:00 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_ast	*new_pipe(void)
{
	t_ast	*pip;

	pip = ft_calloc(1, sizeof(t_ast));
	if (!pip)
		return (NULL);
	pip->cmd = ft_calloc(2, sizeof(char *));
	if (!pip->cmd)
		return (NULL);
	pip->cmd = ft_strdup("|");
	pip->args = ft_matrix_add_line(pip->args, ft_strdup(""));
	return (pip);
}

static t_ast	*parse_pipe(t_ast *prev, t_ast *curr, t_minish *ms)
{
	t_ast	*pip;

	pip = new_pipe();
	if (!pip)
		return (NULL);
	if (prev->cmd[0] != '|')
		prev->next = pip;
	else
		prev->next->next = pip;
	pip->next = curr;
	pip->right = curr;
	if (lastpipe(ms->cmd_list)->index >= 0)
	{
		pip->left = prev;
		pip->index = -1;
	}
	else
	{
		pip->left = lastpipe(ms->cmd_list);
		pip->index = pip->left->index - 1;
	}
	return (pip);
}

static t_token	*parse_redir(t_ast *cmd, t_token *tk)
{
	t_ast	*redir;
	t_ast	*last_redir;

	redir = ft_calloc(1, sizeof(t_ast));
	if (!redir)
		return (NULL);
	redir->cmd = ft_strdup(tk->token);
	redir->args = ft_matrix_add_line(redir->args, ft_strdup(tk->next->token));
	redir->left = NULL;
	redir->right = NULL;
	redir->next = NULL;
	redir->redirections = NULL;
	if (!cmd->redirections)
		cmd->redirections = redir;
	else
	{
		last_redir = cmd->redirections;
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = redir;
	}
	return (tk->next);
}

static t_token	*parse_command(t_minish *ms, t_token *buff)
{
	t_ast	*cmd;

	cmd = ft_calloc(1, sizeof(t_ast));
	if (!cmd)
		return (NULL);
	cmd->next = NULL;
	cmd->left = NULL;
	cmd->right = NULL;
	while (buff && buff->type != PIPE)
	{
		if (buff->type >= REDIR_INPUT_1 && buff->type <= REDIR_OUTPUT_2)
			buff = parse_redir(cmd, buff);
		else if (!cmd->cmd)
		{
			cmd->cmd = ft_strdup(buff->token);
			cmdlst_addback(&ms->cmd_list, cmd);
		}
		else
			cmd->args = ft_matrix_add_line(cmd->args, ft_strdup(buff->token));
		buff = buff->next;
	}
	if (!cmd->args)
		cmd->args = ft_matrix_add_line(cmd->args, ft_strdup("\0"));
	return (buff);
}

void	parse(t_minish *ms)
{
	t_token	*buff;
	t_ast	*prev_cmd;
	t_ast	*curr_cmd;

	buff = parse_command(ms, ms->tk_list);
	if (!buff)
		return ;
	prev_cmd = ms->cmd_list;
	while (buff && buff->type == PIPE)
	{
		buff = parse_command(ms, buff->next);
		curr_cmd = cmdlst_last(ms->cmd_list);
		prev_cmd = parse_pipe(prev_cmd, curr_cmd, ms);
	}
}
