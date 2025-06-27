#include "minishell.h"

int ft_env(t_node *node, t_shell *shell)
{
    int i;

    (void)node; // Not used
    
    if (!shell->env)
        return (shell->exit_status = 1);
    
    i = 0;
    while (shell->env[i])
    {
        if (ft_strchr(shell->env[i], '='))
            printf("%s\n", shell->env[i]);
        i++;
    }
    
    return (shell->exit_status = 0);
}