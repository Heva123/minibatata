#include "../../minishell.h"


t_node	*new_node(t_node_type type)
{
	t_node	*node = calloc(1, sizeof(t_node));
	node->type = type;
	return (node);
}
void	execute_command(t_node *node, char **envp)
{
	pid_t	pid = fork();

	if (pid == 0)
	{
		char *cmd_path = find_command_path(node->args[0], envp);
		if (!cmd_path)
		{
			printf("%s: command not found\n", node->args[0]);
			exit(127);
		}
		execve(cmd_path, node->args, envp);
		perror("execve");
		exit(1);
	}
	else
		waitpid(pid, NULL, 0);
}

void    execute_tree(t_node *node, char **envp)
{
    if (!node)
        return;
    if (node->type == NODE_CMD)
        execute_command(node, envp);
    else if (node->type == NODE_REDIR_OUT)
        execute_redirection_out(node, envp);
    else if (node->type == NODE_REDIR_IN)
        execute_redirection_in(node, envp);
    else if (node->type == NODE_APPEND)
        execute_redirection_append(node, envp);
    else if (node->type == NODE_PIPE)
        execute_pipe_node(node, envp);
}
