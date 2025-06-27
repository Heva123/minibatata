#include "minishell.h"

int ft_exit(t_node *node, t_shell *shell)
{
    int exit_code;

    if (!node || !shell)
        exit(shell->exit_status);
    
    if (!node->args[1])
        exit(shell->exit_status);
    
    if (node->args[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
        return (shell->exit_status = 1);
    }
    
    if (!ft_isnumber(node->args[1]))
    {
        ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
        ft_putstr_fd(node->args[1], STDERR_FILENO);
        ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
        exit(2);
    }
    
    exit_code = ft_atoi(node->args[1]);
    shell->is_running = false;
    exit(exit_code);
}