#include "../../minishell.h"


void	execute_pipe_node(t_node *node, char **envp)
{
	int		pipefd[2];
	pid_t	pid1, pid2;

	pipe(pipefd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]); close(pipefd[1]);
		execute_tree(node->left, envp);
		exit(0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]); close(pipefd[1]);
		execute_tree(node->right, envp);
		exit(0);
	}
	close(pipefd[0]); close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}