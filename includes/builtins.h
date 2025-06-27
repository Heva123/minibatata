#ifndef BUILTINS_H
# define BUILTINS_H

struct s_node;
struct s_shell;
typedef struct s_node t_node;
typedef struct s_shell t_shell;

// Builtin functions
int     ft_echo(t_node *node, t_shell *shell);
int     ft_cd(t_node *node, t_shell *shell);
int     ft_pwd(t_node *node, t_shell *shell);
int     ft_export(t_node *node, t_shell *shell);
int     ft_unset(t_node *node, t_shell *shell);
int     ft_env(t_node *node, t_shell *shell);
int     ft_exit(t_node *node, t_shell *shell);

// Builtin utils
int     is_builtin(char *cmd);
int     execute_builtin(t_node *node, t_shell *shell);
char    *get_env_var(char *var, char **env);
int     set_env_var(char *var, char *value, t_shell *shell);
int     unset_env_var(char *var, t_shell *shell);
void    print_env_vars(char **env);
int     is_valid_identifier(char *str);

#endif