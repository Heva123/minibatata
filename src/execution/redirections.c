/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:20:38 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 19:22:33 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_redirection_out(t_node *node, t_shell *shell)
{
	int	fd;
	int	saved_stdout;

	if (!node || !node->filename || !shell)
		return ;
	fd = open(node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell");
		shell->exit_status = 1;
		return ;
	}
	saved_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execute_tree(node->left, shell);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

void	execute_redirection_in(t_node *node, t_shell *shell)
{
	int	fd;
	int	saved_stdin;

	if (!node || !node->filename || !shell)
		return ;
	fd = open(node->filename, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		shell->exit_status = 1;
		return ;
	}
	saved_stdin = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	execute_tree(node->left, shell);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

void	execute_redirection_append(t_node *node, t_shell *shell)
{
	int	fd;
	int	saved_stdout;

	if (!node || !node->filename || !shell)
		return ;
	fd = open(node->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("minishell");
		shell->exit_status = 1;
		return ;
	}
	saved_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execute_tree(node->left, shell);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}
