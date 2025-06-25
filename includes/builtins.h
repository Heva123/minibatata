// #ifndef BUILTINS_H
// # define BUILTINS_H

// // Forward declaration of t_node
// struct s_node;
// typedef struct s_node t_node;


// // Builtin functions
// int     ft_echo(t_node *node);
// int     ft_cd(t_node *node);
// int     ft_pwd(t_node *node);
// int     ft_export(t_node *node);
// int     ft_unset(t_node *node);
// int     ft_env(t_node *node);
// int     ft_exit(t_node *node);

// // Builtin utils
// int     is_builtin(char *cmd);
// int     execute_builtin(t_node *node, volatile sig_atomic_t *exit_status);
// char    *get_env_var(char *var, char **env);
// int     set_env_var(char *var, char *value, char ***env);
// int     unset_env_var(char *var, char ***env);
// void    print_env_vars(char **env);

// #endif


#ifndef BUILTINS_H
# define BUILTINS_H

// Forward declaration of t_node
struct s_node;
typedef struct s_node t_node;

// Builtin functions
int     ft_echo(t_node *node);
int     ft_cd(t_node *node);
int     ft_pwd(t_node *node);
int     ft_export(t_node *node);
int     ft_unset(t_node *node);
int     ft_env(t_node *node);
int     ft_exit(t_node *node);

// Builtin utils
int     is_builtin(char *cmd);
int     execute_builtin(t_node *node, volatile sig_atomic_t *exit_status);
char    *get_env_var(char *var, char **env);
int     set_env_var(char *var, char *value, char ***env);
int     unset_env_var(char *var, char ***env);
void    print_env_vars(char **env);
int     is_valid_identifier(char *str);

/* --------- Environment Helpers --------- */
char    *ft_itoa(int n);
char    *ft_substr(char const *s, unsigned int start, size_t len);

#endif