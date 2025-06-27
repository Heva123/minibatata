#include "minishell.h"

int ft_echo(t_node *node, t_shell *shell)
{
    int i;
    int newline;

    (void)shell; // Not used but kept for consistency
    if (!node || !node->args)
        return (1);
    
    newline = 1;
    i = 1;
    if (node->args[1] && ft_strcmp(node->args[1], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    
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