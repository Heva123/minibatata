// #include "minishell.h"


// int ft_env(t_node *node)
// {
//     (void)node; 
    
//     print_env_vars(node->env);
//     return (0);
// }

#include "minishell.h"

int ft_env(t_node *node)
{
    int i;

    if (!node || !node->env)
        return (1);
    
    i = 0;
    while (node->env[i])
    {
        // Only print variables with values (VAR=value)
        if (ft_strchr(node->env[i], '='))
            printf("%s\n", node->env[i]);
        i++;
    }
    
    return (0);
}