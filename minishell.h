
// #ifndef MINISHELL_H
// #define MINISHELL_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <sys/wait.h>
// #include <fcntl.h>

// // Tree node types
// typedef enum e_node_type {
//    NODE_CMD,
//     NODE_REDIR_OUT,   // >
//     NODE_REDIR_IN,    // <
//     NODE_APPEND,      // >>
//     NODE_PIPE
// } t_node_type;


// typedef struct s_node {
//     t_node_type type;
//     char **args;
//     char *filename;
//     struct s_node *left;
//     struct s_node *right;
// } t_node;

// //tokonizer

// char	**tokenize_input(const char *input);
// char	*strip_quotes(const char *token);
// int		is_operator(const char *s);
// int		is_quote(char c);
// void	update_quote_state(char c, int *in_single, int *in_double);
// // utils 
// char	**ft_split(char const *s, char c);
// char	*ft_strjoin(char const *s1, char const *s2);
// int	    ft_strncmp(const char *s1, const char *s2, size_t n);
// char	*ft_strchr(const char *s, int c);
// int	    ft_strlen(const char *s);
// char    *ft_strdup(const char *s1);
// char    *ft_strtrim(char const *s1, char const *set);
// void    ft_free(char **arr);
// char	*ft_strrchr(const char *s, int c);

// // execution 
// void    execute_tree(t_node *node, char **envp);
// void	execute_pipe_node(t_node *node, char **envp);
// void    execute_redirection_out(t_node *node, char **envp);
// void    execute_redirection_in(t_node *node, char **envp);
// void    execute_redirection_append(t_node *node, char **envp);

// //parsing
// t_node	*parse_pipe(char *prompt);
// t_node *parse_redir(char *prompt);
// t_node	*parse_prompt(char *prompt);

// //path
// char	**get_paths(char **envp);
// char *find_command_path(char *cmd, char **envp);
// ////////////
// char    **get_paths(char **envp);
// char    *find_command_path(char *cmd, char **envp);
// void    execute_tree(t_node *root, char **envp);
// t_node  *parse_prompt(char *prompt);
// t_node	*new_node(t_node_type type);

// #endif


#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>

// ---------------- Tree node types ----------------
typedef enum e_node_type {
    NODE_CMD,
    NODE_REDIR_OUT,   
    NODE_REDIR_IN,    
    NODE_APPEND,      
    NODE_PIPE
} t_node_type;

typedef struct s_node {
    t_node_type type;
    char **args;
    char *filename;
    struct s_node *left;
    struct s_node *right;
} t_node;

// ---------------- Tokenizer ----------------
char    **tokenize_input(const char *input);
char    *strip_quotes(const char *token);
int     is_operator(const char *s);
int     is_quote(char c);
void    update_quote_state(char c, int *in_single, int *in_double);

// ---------------- Utils ----------------
char    **ft_split(char const *s, char c);
char    *ft_strjoin(char const *s1, char const *s2);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char    *ft_strchr(const char *s, int c);
int     ft_strlen(const char *s);
char    *ft_strdup(const char *s1);
char    *ft_strtrim(char const *s1, char const *set);
void    ft_free(char **arr);
char    *ft_strrchr(const char *s, int c);

// ---------------- Execution ----------------
void    execute_tree(t_node *node, char **envp);
void    execute_pipe_node(t_node *node, char **envp);
void    execute_redirection_out(t_node *node, char **envp);
void    execute_redirection_in(t_node *node, char **envp);
void    execute_redirection_append(t_node *node, char **envp);

// ---------------- Parsing ----------------
t_node  *parse_prompt(char *input);
t_node  *parse_pipe(char *prompt);
t_node  *parse_redir(char *prompt);
t_node  *new_node(t_node_type type);
char    **get_paths(char **envp);
char    *find_command_path(char *cmd, char **envp);
void    update_quote_state(char c, int *in_single, int *in_double);
char    *process_quotes(const char *token);


#endif 
