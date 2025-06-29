/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:23:27 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 19:23:36 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_process(int pipefd[2],
		int fd_to_dup, t_node *node, t_shell *shell)
{
	close(pipefd[!fd_to_dup]);
	dup2(pipefd[fd_to_dup], fd_to_dup + 1);
	close(pipefd[fd_to_dup]);
	execute_tree(node, shell);
	exit(EXIT_SUCCESS);
}

static int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

static int	fork_process(pid_t *pid, int pipefd[2],
		int fd_to_dup, t_node *node, t_shell *shell)
{
	*pid = fork();
	if (*pid == 0)
		handle_child_process(pipefd, fd_to_dup, node, shell);
	if (*pid < 0)
	{
		ft_putstr_fd("minishell: fork error\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

static void	close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	execute_pipe_node(t_node *node, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (!node || !shell)
		return ;
	if (!create_pipe(pipefd))
		return ;
	if (!fork_process(&pid1, pipefd, 1, node->left, shell))
	{
		close_pipe(pipefd);
		return ;
	}
	if (!fork_process(&pid2, pipefd, 0, node->right, shell))
	{
		close_pipe(pipefd);
		waitpid(pid1, NULL, 0);
		return ;
	}
	close_pipe(pipefd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
