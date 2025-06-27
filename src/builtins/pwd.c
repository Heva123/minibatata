#include "minishell.h"

int ft_pwd(t_node *node, t_shell *shell)
{
    char cwd[PATH_MAX];

    (void)node; // Not used
    (void)shell; // Not used
    
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell: pwd");
        return (1);
    }
    
    printf("%s\n", cwd);
    return (0);
}