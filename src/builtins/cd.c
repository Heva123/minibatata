// #include "minishell.h"


// int ft_cd(t_node *node)
// {
//     char *path;
//     char cwd[PATH_MAX];
//     char *oldpwd;
//     char **env;

//     if (!node || !node->args)
//         return (1);
    
//     env = node->env; // You'll need to add env to your t_node struct
    
//     // Get current working directory before changing
//     if (!getcwd(cwd, sizeof(cwd)))
//     {
//         perror("minishell: cd");
//         return (1);
//     }
    
//     // Handle cd with no arguments (go to HOME)
//     if (!node->args[1] || ft_strcmp(node->args[1], "~") == 0)
//     {
//         path = get_env_var("HOME", env);
//         if (!path)
//         {
//             ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
//             return (1);
//         }
//     }
//     // Handle cd -
//     else if (ft_strcmp(node->args[1], "-") == 0)
//     {
//         path = get_env_var("OLDPWD", env);
//         if (!path)
//         {
//             ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
//             return (1);
//         }
//         printf("%s\n", path);
//     }
//     else
//         path = node->args[1];
    
//     // Change directory
//     if (chdir(path) != 0)
//     {
//         perror("minishell: cd");
//         return (1);
//     }
    
//     // Update PWD and OLDPWD
//     oldpwd = ft_strdup(cwd);
//     set_env_var("OLDPWD", oldpwd, &env);
//     free(oldpwd);
    
//     if (!getcwd(cwd, sizeof(cwd)))
//     {
//         perror("minishell: cd");
//         return (1);
//     }
//     set_env_var("PWD", cwd, &env);
    
//     return (0);
// }

#include "minishell.h"

int ft_cd(t_node *node)
{
    char *path;
    char cwd[PATH_MAX];
    char *oldpwd;

    if (!node || !node->args)
        return (1);
    
    // Get current directory before changing
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell: cd");
        return (1);
    }
    
    // Handle cd with no arguments (go to HOME)
    if (!node->args[1] || ft_strcmp(node->args[1], "~") == 0)
    {
        path = get_env_var("HOME", node->env);
        if (!path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
            return (1);
        }
    }
    // Handle cd -
    else if (ft_strcmp(node->args[1], "-") == 0)
    {
        path = get_env_var("OLDPWD", node->env);
        if (!path)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
            return (1);
        }
        printf("%s\n", path);
    }
    else
        path = node->args[1];
    
    // Change directory
    if (chdir(path) != 0)
    {
        perror("minishell: cd");
        return (1);
    }
    
    // Update PWD and OLDPWD
    oldpwd = ft_strdup(cwd);
    set_env_var("OLDPWD", oldpwd, &node->env);
    free(oldpwd);
    
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell: cd");
        return (1);
    }
    set_env_var("PWD", cwd, &node->env);
    
    return (0);
}