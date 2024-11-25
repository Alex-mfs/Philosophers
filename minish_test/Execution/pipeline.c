/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:44:12 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/25 21:43:52 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipe_data_flow(int cmd_index, t_minish *ms, char **fullcmd)
{
	int	cmd_num;

	cmd_num = cmdlst_size(ms->cmd_list, false);
	if (cmd_num <= 1)
		return ;
	if (cmd_index > 0 && ms->fd_in == STDIN_FILENO)
		ms->fd_in = ms->pipes[cmd_index - 1][0];
	if (cmd_index < cmd_num - 1 && ms->fd_out == STDOUT_FILENO)
	{
		if (fullcmd && !get_executable_path(*fullcmd, ms))
			error("minishell: Command not found\n", 127);
		ms->fd_out = ms->pipes[cmd_index][1];
	}
}

void	relinking_in_out(t_minish *ms)
{
	if (ms->fd_in >= STDIN_FILENO)
	{
		if (dup2(ms->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 fd_in");
			exit(EXIT_FAILURE);
		}
	}
	if (ms->fd_out >= STDOUT_FILENO)
	{
		if (dup2(ms->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 fd_out");
			exit(EXIT_FAILURE);
		}
	}
}

//       /    /   chatgpt sugeriu \     \     \  \\ //
// void	relinking_in_out(t_minish *ms)
// {
// 	if (ms->fd_in != STDIN_FILENO)
// 	{
// 		if (dup2(ms->fd_in, STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 fd_in");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(ms->fd_in); // Close after duplicating
// 	}
// 	if (ms->fd_out != STDOUT_FILENO)
// 	{
// 		if (dup2(ms->fd_out, STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2 fd_out");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(ms->fd_out); // Close after duplicating
// 	}
// }

void	close_in_out(int index, t_minish *ms)
{
	if (ms->fd_in > STDIN_FILENO)
		close(ms->fd_in);
	if (ms->fd_out > STDOUT_FILENO)
		close(ms->fd_out);
	if (index > 0)
		close(ms->pipes[index - 1][0]);
	if (index != (cmdlst_size(ms->cmd_list, false) - 1))
		close(ms->pipes[index][1]);
	ms->fd_in = 0;
	ms->fd_out = 1;
}

//     /   /   /  /   chatgpt sugeriu \ \  \  \  \ //
// void	close_in_out(int index, t_minish *ms)
// {
// 	if (ms->fd_in > STDERR_FILENO)
// 		close(ms->fd_in);
// 	if (ms->fd_out > STDERR_FILENO)
// 		close(ms->fd_out);
// 	if (index > 0)
// 		close(ms->pipes[index - 1][0]);
// 	if (index != (cmdlst_size(ms->cmd_list, false) - 1))
// 		close(ms->pipes[index][1]);
// 	ms->fd_in = STDIN_FILENO;
// 	ms->fd_out = STDOUT_FILENO;
// }

void	count_pipes(t_minish *ms)
{
	t_token *aux;

	aux = ms->tk_list;
	while (aux)
	{
		if (aux->type == PIPE)
			ms->qtd_pipes++;
		aux = aux->next;
	}
}

void	pipeline_matrix(t_minish *ms)
{
	int	i;

	i = 0;
	count_pipes(ms);
	if (cmdlst_size(ms->cmd_list, false) == 1)
		return ;
	ms->pipes = ft_calloc(cmdlst_size(ms->cmd_list, false) - 1, sizeof(int *));
	if (!ms->pipes)
		return ;
	while (i < (cmdlst_size(ms->cmd_list, false) - 1))
	{
		ms->pipes[i] = ft_calloc(2, sizeof(int));
		if (!ms->pipes[i])
			return ;
		pipe(ms->pipes[i]);
		i++;
	}
}
