#include "minishell.h"


int ft_env(t_node *node)
{
    (void)node; 
    
    print_env_vars(node->env);
    return (0);
}