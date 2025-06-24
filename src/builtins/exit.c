#include "minishell.h"


int ft_exit(t_node *node)
{
    int exit_code;
    char *arg;

    if (!node || !node->args)
        exit(0);
    
    // If no arguments, exit with 0
    if (!node->args[1])
        exit(0);
    
    // Check if argument is numeric
    arg = node->args[1];
    while (*arg)
    {
        if (!ft_isdigit(*arg))
        {
            ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
            ft_putstr_fd(node->args[1], STDERR_FILENO);
            ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
            exit(2);
        }
        arg++;
    }
    
    // If more than one argument
    if (node->args[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
        return (1);
    }
    
    exit_code = ft_atoi(node->args[1]);
    exit(exit_code);
}