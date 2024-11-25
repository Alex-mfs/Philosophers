/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/25 21:46:19 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_if_exists(char **arg, t_minish *ms)
{
	char		*path;
	struct stat	path_stat;

	path = get_executable_path(*arg, ms);
	if (!path || stat(path, &path_stat) != 0)
	{
		ft_free_matrix(arg);
		error("minishell: command not found\n", 127);
		sanitize_ms(ms, true);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_free_matrix(arg);
		error("minishell: is a directory\n", 126);
		sanitize_ms(ms, true);
	}
	execve(path, arg, ms->env_list);
	error("minishell: permission denied or execution failed\n", 126);
	exit(126);
}

void	do_command(char	*cmd, char **args, t_minish *ms)
{
	char	**full_cmd;

	set_exit_status(0);
	if (!is_builtin(cmd))
	{
		if (ms->dont_execve)
			return ;
		full_cmd = join_cmd_arg(cmd, args);
		exec_if_exists(full_cmd, ms);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	if (ft_str_cmp(cmd, "pwd"))
		printf("%s\n", ms->cwd);
	else if (ft_str_cmp(cmd, "echo"))
		echo(args);
	else if (ft_str_cmp(cmd, "exit"))
		exit_bash(args, ms);
	else if (ft_str_cmp(cmd, "env"))
		env(args, ms->env_list);
	else if (ft_str_cmp(cmd, "export"))
		ft_export(args, ms);
	else if (ft_str_cmp(cmd, "unset"))
		unset(args, ms);
	else if (ft_str_cmp(cmd, "cd"))
		cd(args, ms);
}

void create_fullcmd_pipe_flow(t_minish *ms, t_ast *node)
{
	char	**fullcmd;

	fullcmd = join_cmd_arg(node->cmd, node->args);
	pipe_data_flow(node->index, ms, fullcmd);
	ft_free_matrix(fullcmd);
}

pid_t	child_exec(t_ast *node, t_minish *ms)
{
	pid_t	pid;

	treat_child_signal();
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: Error while creating child process");
		return (-1);
	}
	if (pid == 0)
	{
		if (ms->fd_in == -1 || ms->fd_out == -1)
			sanitize_ms(ms, true);
		if (!is_builtin(node->cmd))
			create_fullcmd_pipe_flow(ms, node);
		else
			pipe_data_flow(node->index, ms, NULL);
		relinking_in_out(ms);
		do_command(node->cmd, node->args, ms);
		sanitize_ms(ms, true);
	}
	close_in_out(node->index, ms);
	return (pid);
}

pid_t	pipeline_exec(t_ast	*node, t_minish *ms)
{
	pid_t	last_child_pid;
	t_ast	*redir_node;

	last_child_pid = 0;
	if (!node)
		return (last_child_pid);
	ms->dont_execve = false;
	last_child_pid = pipeline_exec(node->left, ms);
	last_child_pid = pipeline_exec(node->right, ms);
	if (!is_redir_or_pipe(node->cmd))
	{
		redir_node = node->redirections;
		while (redir_node)
		{
			execute_redir(redir_node->cmd, redir_node->args[0], ms);
			redir_node = redir_node->next;		
		}
		if (need2be_parent(node->cmd, node->args[0], ms))
			do_command(node->cmd, node->args, ms);
		else
			last_child_pid = child_exec(node, ms);
	}
	else if (is_redirection(node->cmd))
		execute_redir(node->cmd, node->args[0], ms);
	return (last_child_pid);
}

void	execute(t_minish *ms)
{
	int		status;
	pid_t	last;
	t_ast	*head;
	// int		original_stdin; chat
	// int		original_stdout;

	head = lastpipe(ms->cmd_list);
	status = 0x7F;
	// original_stdin = dup(STDIN_FILENO); chat
	// original_stdout = dup(STDOUT_FILENO);
	pipeline_matrix(ms);
	last = pipeline_exec(head, ms);
	last = waitpid(last, &status, 0);
	while (waitpid(0, NULL, 0) > 0)
		continue ;
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
	set_signals();
	// dup2(original_stdin, STDIN_FILENO); chat
	// dup2(original_stdout, STDOUT_FILENO);
	// close(original_stdin);
	// close(original_stdout);
}
