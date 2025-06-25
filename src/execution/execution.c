#include "minishell.h"
#include "signals.h"

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
    pid_t pid;
    int status;

    if (!node || !node->args || !node->args[0])
        return;
    
    if (is_builtin(node->args[0]))
    {
        // Handle builtins directly
        execute_builtin(node, &g_signal_status);
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        // Child process - set execution signals
        setup_exec_signals();
        
        char *cmd_path = find_command_path(node->args[0], envp);
        if (!cmd_path)
        {
            ft_putstr_fd(node->args[0], STDERR_FILENO);
            ft_putstr_fd(": command not found\n", STDERR_FILENO);
            exit(127);
        }
        execve(cmd_path, node->args, envp);
        perror("minishell");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("minishell: fork");
        return;
    }
    
    // Parent process - wait for child and get exit status
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        g_signal_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        g_signal_status = 128 + WTERMSIG(status);
    
    // Restore shell signals after command execution
    restore_shell_signals();
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
