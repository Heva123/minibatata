
#include "../../minishell.h"

void execute_redirection_out(t_node *node, char **envp)
{
    int fd;
    int saved_stdout;

    if (!node || !node->filename)
        return;
    fd = open(node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        return;
    }
    saved_stdout = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    execute_tree(node->left, envp);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
}

void execute_redirection_in(t_node *node, char **envp)
{
    int fd;
    int saved_stdin;

    if (!node || !node->filename)
        return;
    fd = open(node->filename, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return;
    }
    saved_stdin = dup(STDIN_FILENO);
    dup2(fd, STDIN_FILENO);
    close(fd);
    execute_tree(node->left, envp);
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdin);
}

void execute_redirection_append(t_node *node, char **envp)
{
    int fd;
    int saved_stdout;

    if (!node || !node->filename)
        return;
    fd = open(node->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd < 0)
    {
        perror("open");
        return;
    }
    saved_stdout = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    execute_tree(node->left, envp);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
}