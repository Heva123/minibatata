#include "minishell.h"


int ft_echo(t_node *node)
{
    int i;
    int newline;

    if (!node || !node->args)
        return (1);
    
    newline = 1;
    i = 1;
    
    // Check for -n option
    if (node->args[i] && ft_strcmp(node->args[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    
    // Print arguments
    while (node->args[i])
    {
        printf("%s", node->args[i]);
        if (node->args[i + 1])
            printf(" ");
        i++;
    }
    
    if (newline)
        printf("\n");
    
    return (0);
}