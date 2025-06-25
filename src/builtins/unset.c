// #include "minishell.h"

// int ft_unset(t_node *node)
// {
//     int i;
//     int ret;

//     if (!node || !node->args)
//         return (1);
    
//     ret = 0;
//     i = 1;
//     while (node->args[i])
//     {
//         if (!is_valid_identifier(node->args[i]))
//         {
//             ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
//             ft_putstr_fd(node->args[i], STDERR_FILENO);
//             ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
//             ret = 1;
//         }
//         else
//         {
//             if (unset_env_var(node->args[i], &node->env) != 0)
//                 ret = 1;
//         }
//         i++;
//     }
    
//     return (ret);
// }

#include "minishell.h"

int ft_unset(t_node *node)
{
    int i;
    int ret;

    if (!node || !node->args)
        return (1);
    
    ret = 0;
    i = 1;
    while (node->args[i])
    {
        if (!is_valid_identifier(node->args[i]))
        {
            ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
            ft_putstr_fd(node->args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            ret = 1;
        }
        else
        {
            if (unset_env_var(node->args[i], &node->env) != 0)
                ret = 1;
        }
        i++;
    }
    
    return (ret);
}