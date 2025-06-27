
#include "minishell.h"

t_shell  *init_shell(char **envp)
{
    t_shell *shell;
    
    shell = calloc(1, sizeof(t_shell));
    if (!shell)
        return (NULL);
    
    shell->env = copy_env(envp);
    shell->exit_status = 0;
    shell->is_running = true;
    update_pwd_vars(shell);
    
    return (shell);
}

void cleanup_shell(t_shell *shell)
{
    if (!shell)
        return;
    
    ft_free_strarr(shell->env);
    free(shell->pwd);
    free(shell->oldpwd);
    free(shell);
}