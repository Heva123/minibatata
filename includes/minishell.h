/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:26:16 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 18:38:50 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include "builtins.h"
# include "signals.h"

// ---------------- Tree node types ----------------
typedef enum e_node_type
{
	NODE_CMD,
	NODE_REDIR_OUT,
	NODE_REDIR_IN,
	NODE_APPEND,
	NODE_PIPE,
	NODE_HEREDOC,
}		t_node_type;

typedef struct s_shell
{
	char	**env;
	int		exit_status;
	bool	is_running;
	char	*pwd;
	char	*oldpwd;
}		t_shell;

typedef struct s_node
{
	t_node_type		type;
	char			**args;
	char			*filename;
	struct s_node	*left;
	struct s_node	*right;
	t_shell			*shell;
}		t_node;

/* Add to existing prototypes */
t_shell		*init_shell(char **envp);
void		cleanup_shell(t_shell *shell);
char		**copy_env(char **envp);
void		update_pwd_vars(t_shell *shell);

// ---------------- Tokenizer ----------------
char		**tokenize_input(const char *input);
char		*strip_quotes(const char *token);
int			is_operator(const char *s);
int			is_quote(char c);
void		update_quote_state(char c, int *in_single, int *in_double);

// ---------------- Utils ----------------
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
int			ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_strtrim(char const *s1, char const *set);
void		ft_free(char **arr);
char		*ft_strrchr(const char *s, int c);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strndup(const char *s, size_t n);
void		ft_putstr_fd(char *s, int fd);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isnumber(const char *str);
int			ft_atoi(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_itoa(int n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_sort_strarr(char **arr);
void		free_ast(t_node *node);
void		ft_free_strarr(char **arr);

/* --------- Expansion Helpers --------- */
bool		in_double_quote(char *input, int pos);
int			handle_single_quotes(char **result, char *input, int i);
int			handle_double_quotes(char **result, char *input, int i,
				int last_exit_status, char **env);
int			append_char(char **result, char c);
void		append_to_result(char **result, char *to_append);
int			handle_pid_var(char **result, char *input, int *i);
int			expand_variables(t_node *node);
char		*expand_str(char *input, int last_exit_status, char **env);
int			handle_exit_status_var(char **result, char *input, int *i);
int			andle_env_var(char **result, char *input, int *i, char **env);
bool		is_valid_var_char(char c);
int			handle_special_vars(char **result, char *input, int *i, char **env);

// ---------------- Execution ----------------
void		execute_tree(t_node *node, t_shell *shell);
void		execute_command(t_node *node, t_shell *shell);
void		execute_pipe_node(t_node *node, t_shell *shell);
void		execute_redirection_out(t_node *node, t_shell *shell);
void		execute_redirection_in(t_node *node, t_shell *shell);
void		execute_redirection_append(t_node *node, t_shell *shell);
void		execute_heredoc(t_node *node, t_shell *shell);

// ---------------- Parsing ----------------
t_node		*parse_prompt(char *input);
t_node		*parse_pipe(char *prompt);
t_node		*parse_redir(char *prompt);
t_node		*new_node(t_node_type type);
char		**get_paths(char **envp);
char		*find_command_path(char *cmd, char **envp);
void		update_quote_state(char c, int *in_single, int *in_double);
char		*process_quotes(const char *token);
t_node		*parse_command(char *cmd_str);

#endif
