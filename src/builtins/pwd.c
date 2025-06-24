#include "minishell.h"


int ft_pwd(t_node *node)
{
    char cwd[PATH_MAX];

    (void)node; // Unused parameter
    
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell: pwd");
        return (1);
    }
    
    printf("%s\n", cwd);
    return (0);
}