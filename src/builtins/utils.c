#include "minishell.h"


int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    if (ft_strcmp(cmd, "echo") == 0)
        return (1);
    if (ft_strcmp(cmd, "cd") == 0)
        return (1);
    if (ft_strcmp(cmd, "pwd") == 0)
        return (1);
    if (ft_strcmp(cmd, "export") == 0)
        return (1);
    if (ft_strcmp(cmd, "unset") == 0)
        return (1);
    if (ft_strcmp(cmd, "env") == 0)
        return (1);
    if (ft_strcmp(cmd, "exit") == 0)
        return (1);
    return (0);
}

int execute_builtin(t_node *node, volatile sig_atomic_t *exit_status)
{
    if (!node || !node->args || !node->args[0])
        return (0);
    
    if (ft_strcmp(node->args[0], "echo") == 0)
        *exit_status = ft_echo(node);
    else if (ft_strcmp(node->args[0], "cd") == 0)
        *exit_status = ft_cd(node);
    else if (ft_strcmp(node->args[0], "pwd") == 0)
        *exit_status = ft_pwd(node);
    else if (ft_strcmp(node->args[0], "export") == 0)
        *exit_status = ft_export(node);
    else if (ft_strcmp(node->args[0], "unset") == 0)
        *exit_status = ft_unset(node);
    else if (ft_strcmp(node->args[0], "env") == 0)
        *exit_status = ft_env(node);
    else if (ft_strcmp(node->args[0], "exit") == 0)
        *exit_status = ft_exit(node);
    else
        return (0);
    
    return (1);
}

char *get_env_var(char *var, char **env)
{
    int i;
    int len;

    if (!var || !env)
        return (NULL);
    
    len = ft_strlen(var);
    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
            return (env[i] + len + 1);
        i++;
    }
    return (NULL);
}

int set_env_var(char *var, char *value, char ***env)
{
    int i;
    int len;
    char *new_var;
    char **new_env;

    if (!var || !env || !*env)
        return (1);
    
    len = ft_strlen(var);
    i = 0;
    while ((*env)[i])
    {
        if (ft_strncmp((*env)[i], var, len) == 0 && (*env)[i][len] == '=')
        {
            free((*env)[i]);
            new_var = ft_strjoin(var, "=");
            (*env)[i] = ft_strjoin(new_var, value);
            free(new_var);
            return (0);
        }
        i++;
    }
    
    // Variable not found, add it
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return (1);
    
    i = 0;
    while ((*env)[i])
    {
        new_env[i] = ft_strdup((*env)[i]);
        i++;
    }
    
    new_var = ft_strjoin(var, "=");
    new_env[i] = ft_strjoin(new_var, value);
    free(new_var);
    new_env[i + 1] = NULL;
    
    ft_free(*env);
    *env = new_env;
    return (0);
}

int unset_env_var(char *var, char ***env)
{
    int i;
    int j;
    int len;
    char **new_env;

    if (!var || !env || !*env)
        return (1);
    
    len = ft_strlen(var);
    i = 0;
    while ((*env)[i])
    {
        if (ft_strncmp((*env)[i], var, len) == 0 && 
            ((*env)[i][len] == '=' || (*env)[i][len] == '\0'))
        {
            // Found the variable, create new env without it
            new_env = malloc(sizeof(char *) * i);
            if (!new_env)
                return (1);
            
            j = 0;
            while (j < i)
            {
                new_env[j] = ft_strdup((*env)[j]);
                j++;
            }
            
            while ((*env)[j + 1])
            {
                new_env[j] = ft_strdup((*env)[j + 1]);
                j++;
            }
            new_env[j] = NULL;
            
            ft_free(*env);
            *env = new_env;
            return (0);
        }
        i++;
    }
    return (0);
}

void print_env_vars(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}

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