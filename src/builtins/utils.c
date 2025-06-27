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

int execute_builtin(t_node *node, t_shell *shell)
{
    if (!node || !node->args || !node->args[0] || !shell)
        return (0);
    
    if (ft_strcmp(node->args[0], "echo") == 0)
        return (ft_echo(node, shell));
    else if (ft_strcmp(node->args[0], "cd") == 0)
        return (ft_cd(node, shell));
    else if (ft_strcmp(node->args[0], "pwd") == 0)
        return (ft_pwd(node, shell));
    else if (ft_strcmp(node->args[0], "export") == 0)
        return (ft_export(node, shell));
    else if (ft_strcmp(node->args[0], "unset") == 0)
        return (ft_unset(node, shell));
    else if (ft_strcmp(node->args[0], "env") == 0)
        return (ft_env(node, shell));
    else if (ft_strcmp(node->args[0], "exit") == 0)
        return (ft_exit(node, shell));
    
    return (0);
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

int set_env_var(char *var, char *value, t_shell *shell)
{
    char *env_str;
    char **new_env;
    int count = 0;
    int i = 0;

    if (!var || !shell || !shell->env)
        return 1;
    
    // Create the new environment string
    env_str = ft_strjoin(var, "=");
    if (!env_str)
        return 1;
    char *tmp = env_str;
    env_str = ft_strjoin(env_str, value ? value : "");
    free(tmp);
    if (!env_str)
        return 1;
    
    // Check if variable exists
    while (shell->env[count] && ft_strncmp(shell->env[count], var, ft_strlen(var)) != 0)
        count++;
    
    if (shell->env[count])
    {
        // Replace existing variable
        free(shell->env[count]);
        shell->env[count] = env_str;
        return 0;
    }
    
    // Add new variable
    while (shell->env[i]) i++;
    new_env = calloc(i + 2, sizeof(char *));
    if (!new_env)
    {
        free(env_str);
        return 1;
    }
    
    for (int j = 0; j < i; j++)
        new_env[j] = shell->env[j];
    
    new_env[i] = env_str;
    free(shell->env);
    shell->env = new_env;
    return 0;
}

int unset_env_var(char *var, t_shell *shell)
{
    int i;
    int j;
    int len;
    char **new_env;

    if (!var || !shell || !shell->env)
        return 1;
    
    len = ft_strlen(var);
    i = 0;
    while (shell->env[i])
    {
        if (ft_strncmp(shell->env[i], var, len) == 0 && 
            (shell->env[i][len] == '=' || shell->env[i][len] == '\0'))
        {
            // Found the variable
            new_env = calloc(i, sizeof(char *));
            if (!new_env)
                return 1;
            
            j = 0;
            while (j < i)
            {
                new_env[j] = ft_strdup(shell->env[j]);
                j++;
            }
            
            while (shell->env[j + 1])
            {
                new_env[j] = ft_strdup(shell->env[j + 1]);
                j++;
            }
            new_env[j] = NULL;
            
            ft_free_strarr(shell->env);
            shell->env = new_env;
            return 0;
        }
        i++;
    }
    return 0;
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