
 #include "minishell.h"

t_node *new_node(t_node_type type)
{
    t_node *node = calloc(1, sizeof(t_node));
    if (!node)
        return NULL;
    node->type = type;
    return node;
}


void execute_command(t_node *node, char **envp)
{
    int exit_status;

    if (!node || !node->args || !node->args[0])
        return;
    
    // Check if it's a builtin
    if (is_builtin(node->args[0]))
    {
        execute_builtin(node, &exit_status);
        // You might want to store exit_status somewhere
        return;
    }
    
    // Rest of your existing execute_command code...
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        char *cmd_path = find_command_path(node->args[0], envp);
        if (!cmd_path)
        {
            write(2, node->args[0], ft_strlen(node->args[0]));
            write(2, ": command not found\n", 21);
            exit(127);
        }
        execve(cmd_path, node->args, envp);
        perror("execve"); 
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        write(2, "fork failed\n", 12);
        return;
    }
    waitpid(pid, NULL, 0);
}



void execute_tree(t_node *node, char **envp)
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
    else if (node->type == NODE_HEREDOC) 
        execute_heredoc(node, envp);
}
