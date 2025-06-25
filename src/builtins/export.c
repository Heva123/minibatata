#include "minishell.h"

int is_valid_identifier(char *str)
{
    int i;

    if (!str || !*str || ft_isdigit(*str))
        return (0);
    
    i = 0;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int ft_export(t_node *node)
{
    int i;
    int ret;
    char *equal_sign;
    char *var;
    char *value;

    if (!node || !node->args)
        return (1);
    
    // If no arguments, print all exported variables
    if (!node->args[1])
    {
        print_env_vars(node->env);
        return (0);
    }
    
    ret = 0;
    i = 1;
    while (node->args[i])
    {
        if (!is_valid_identifier(node->args[i]))
        {
            ft_putstr_fd("minishell: export: `", STDERR_FILENO);
            ft_putstr_fd(node->args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            ret = 1;
            i++;
            continue;
        }
        
        equal_sign = ft_strchr(node->args[i], '=');
        if (equal_sign)
        {
            *equal_sign = '\0';
            var = node->args[i];
            value = equal_sign + 1;
            if (set_env_var(var, value, &node->env) != 0)
                ret = 1;
        }
        i++;
    }
    
    return (ret);
}