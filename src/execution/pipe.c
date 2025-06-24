#include "minishell.h"

static void	handle_child_process(int pipefd[2], int fd_to_dup, t_node *node, char **envp)
{
	close(pipefd[!fd_to_dup]);
	dup2(pipefd[fd_to_dup], fd_to_dup + 1);
	close(pipefd[fd_to_dup]);
	execute_tree(node, envp);
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

static int	fork_process(pid_t *pid, int pipefd[2], int fd_to_dup, t_node *node, char **envp)
{
	*pid = fork();
	if (*pid == 0)
		handle_child_process(pipefd, fd_to_dup, node, envp);
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

void	execute_pipe_node(t_node *node, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (!node)
		return ;
	if (!create_pipe(pipefd))
		return ;
	if (!fork_process(&pid1, pipefd, 1, node->left, envp))
	{
		close_pipe(pipefd);
		return ;
	}
	if (!fork_process(&pid2, pipefd, 0, node->right, envp))
	{
		close_pipe(pipefd);
		waitpid(pid1, NULL, 0);
		return ;
	}
	close_pipe(pipefd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}