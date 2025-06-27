#include "minishell.h"

int ft_cd(t_node *node, t_shell *shell)
{
    char *path;
    char cwd[PATH_MAX];
    char *oldpwd;

    if (!node || !node->args)
        return (shell->exit_status = 1);
    
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell: cd");
        return (shell->exit_status = 1);
    }
    
    if (!node->args[1] || ft_strcmp(node->args[1], "~") == 0)
    {
        path = get_env_var("HOME", shell->env);
        if (!path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
            return (shell->exit_status = 1);
        }
    }
    else if (ft_strcmp(node->args[1], "-") == 0)
    {
        path = get_env_var("OLDPWD", shell->env);
        if (!path)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
            return (shell->exit_status = 1);
        }
        printf("%s\n", path);
    }
    else
        path = node->args[1];
    
    if (chdir(path) != 0)
    {
        perror("minishell: cd");
        return (shell->exit_status = 1);
    }
    
    oldpwd = ft_strdup(cwd);
    set_env_var("OLDPWD", oldpwd, shell);
    free(oldpwd);
    
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell: cd");
        return (shell->exit_status = 1);
    }
    set_env_var("PWD", cwd, shell);
    
    return (shell->exit_status = 0);
}