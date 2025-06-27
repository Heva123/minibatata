#include "minishell.h"

char **copy_env(char **envp)
{
    char **new_env;
    int count = 0;
    int i = 0;
    
    if (!envp)
        return NULL;
    
    while (envp[count]) 
        count++;
    
    new_env = calloc(count + 1, sizeof(char *));
    if (!new_env) 
        return NULL;
    
    while (i < count)
    {
        new_env[i] = ft_strdup(envp[i]);
        if (!new_env[i])
        {
            ft_free_strarr(new_env);
            return NULL;
        }
        i++;
    }
    return new_env;
}

char *get_env_value(const char *var, t_shell *shell)
{
    char *value;
    
    if (!var || !shell || !shell->env)
        return NULL;
    
    value = get_env_var((char *)var, shell->env);
    return (value ? ft_strdup(value) : NULL);
}

void update_pwd_vars(t_shell *shell)
{
    char *cwd;
    char *oldpwd;

    if (!shell)
        return;
    
    cwd = getcwd(NULL, 0);
    if (!cwd)
        return;
    
    oldpwd = get_env_value("PWD", shell);
    if (set_env_var("OLDPWD", oldpwd, shell) != 0)
    {
        free(cwd);
        free(oldpwd);
        return;
    }
    
    if (set_env_var("PWD", cwd, shell) != 0)
    {
        free(cwd);
        free(oldpwd);
        return;
    }
    
    free(shell->pwd);
    shell->pwd = cwd;
    
    if (oldpwd)
    {
        free(shell->oldpwd);
        shell->oldpwd = ft_strdup(oldpwd);
        free(oldpwd);
    }
}