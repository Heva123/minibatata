/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:27:27 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 19:30:54 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(t_node_type type)
{
	t_node	*node;

	node = calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}

void	execute_command(t_node *node, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	if (!node || !node->args || !node->args[0] || !shell)
		return ;
	if (expand_variables(node) != 0)
	{
		shell->exit_status = 1;
		return ;
	}
	if (is_builtin(node->args[0]))
	{
		execute_builtin(node, shell);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		setup_exec_signals();
		cmd_path = find_command_path(node->args[0], shell->env);
		if (!cmd_path)
		{
			if (ft_strchr(node->args[0], '/'))
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(node->args[0], STDERR_FILENO);
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			}
			else
			{
				ft_putstr_fd(node->args[0], STDERR_FILENO);
				ft_putstr_fd(": command not found\n", STDERR_FILENO);
			}
			exit(127);
		}
		execve(cmd_path, node->args, shell->env);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("minishell: fork");
		shell->exit_status = 1;
		return ;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	restore_shell_signals();
}

void	execute_tree(t_node *node, t_shell *shell)
{
	if (!node || !shell)
		return ;
	if (node->type == NODE_CMD)
		execute_command(node, shell);
	else if (node->type == NODE_REDIR_OUT)
		execute_redirection_out(node, shell);
	else if (node->type == NODE_REDIR_IN)
		execute_redirection_in(node, shell);
	else if (node->type == NODE_APPEND)
		execute_redirection_append(node, shell);
	else if (node->type == NODE_PIPE)
		execute_pipe_node(node, shell);
	else if (node->type == NODE_HEREDOC)
		execute_heredoc(node, shell);
}
