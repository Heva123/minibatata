#include "minishell.h"

void append_to_result(char **result, char *to_append)
{
    char *tmp;

    tmp = ft_strjoin(*result, to_append);
    if (!tmp)
        return;  // or handle error
    free(*result);
    *result = tmp;
}

int	handle_exit_status_var(char **result, char *input, int *i)
{
	char	*exit_str;
	char	*tmp;

	(void)input;
	exit_str = ft_itoa(g_signal_status);
	if (!exit_str)
		return (0);
	tmp = ft_strjoin(*result, exit_str);
	free(exit_str);
	if (!tmp)
		return (0);
	free(*result);
	*result = tmp;
	*i += 2;
	return (1);
}

int	handle_env_var(char **result, char *input, int *i, char **env)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*tmp;

	start = ++(*i);
	while (input[*i] && is_valid_var_char(input[*i]))
		(*i)++;
	var_name = ft_substr(input, start, *i - start);
	if (!var_name)
		return (0);
	var_value = get_env_var(var_name, env);
	free(var_name);
	tmp = ft_strjoin(*result, var_value ? var_value : "");
	if (!tmp)
		return (0);
	free(*result);
	*result = tmp;
	return (1);
}

int	append_char(char **result, char c)
{
	char	*tmp;
	char	small_str[2];

	small_str[0] = c;
	small_str[1] = '\0';
	tmp = ft_strjoin(*result, small_str);
	if (!tmp)
		return (0);
	free(*result);
	*result = tmp;
	return (1);
}

bool	in_double_quote(char *input, int pos)
{
	int	i;
	bool	in_dquote;

	i = 0;
	in_dquote = false;
	while (i < pos)
	{
		if (input[i] == '"' && (i == 0 || input[i - 1] != '\\'))
			in_dquote = !in_dquote;
		i++;
	}
	return (in_dquote);
}

int	handle_single_quotes(char **result, char *input, int i)
{
	int	start;
	char	*quoted;

	start = i++;
	while (input[i] && input[i] != '\'')
		i++;
	if (!input[i])
		return (append_char(result, '\''));
	quoted = ft_substr(input, start + 1, i - start - 1);
	if (!quoted)
		return (0);
	append_to_result(result, quoted);
	free(quoted);
	return (i - start + 1);
}

int	handle_double_quotes(char **result, char *input, int i, int last_exit_status, char **env)
{
	int		start;
	char	*content;
	char	*expanded;

	start = i++;
	while (input[i] && input[i] != '"')
	{
		if (input[i] == '$' && input[i + 1] && 
			(is_valid_var_char(input[i + 1]) || input[i + 1] == '?'))
			i += handle_special_vars(result, input, &i, env);
		else
			i += append_char(result, input[i]);
	}
	if (!input[i])
		return (append_char(result, '"'));
	content = ft_substr(input, start + 1, i - start - 1);
	if (!content)
		return (0);
	expanded = expand_str(content, last_exit_status, env);
	free(content);
	append_to_result(result, expanded);
	free(expanded);
	return (i - start + 1);
}