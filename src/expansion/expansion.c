/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:18:15 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 19:20:24 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

int	handle_pid_var(char **result, char *input, int *i)
{
	char	*pid_str;
	char	*tmp;

	(void)input;
	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (0);
	tmp = ft_strjoin(*result, pid_str);
	free(pid_str);
	if (!tmp)
		return (0);
	free(*result);
	*result = tmp;
	*i += 2;
	return (1);
}

bool	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	handle_special_vars(char **result, char *input, int *i, char **env)
{
	if (input[*i + 1] == '?')
		return (handle_exit_status_var(result, input, i));
	else if (input[*i + 1] == '$')
		return (handle_pid_var(result, input, i));
	else
		return (handle_env_var(result, input, i, env));
}

char	*expand_str(char *input, int last_exit_status, char **env)
{
	char	*result;
	int		i;
	int		len;

	result = ft_strdup("");
	i = 0;
	len = ft_strlen(input);
	while (i < len)
	{
		if (input[i] == '\'' && !in_double_quote(input, i))
			i += handle_single_quotes(&result, input, i);
		else if (input[i] == '"')
			i += handle_double_quotes(&result, input, i, last_exit_status, env);
		else if (input[i] == '$' && input[i + 1]
			&& (is_valid_var_char(input[i + 1]) || input[i + 1] == '?'))
			i += handle_special_vars(&result, input, &i, env);
		else
			i += append_char(&result, input[i]);
	}
	return (result);
}

int	expand_variables(t_node *node)
{
	int		i;
	char	*expanded;

	if (!node || !node->args || !node->shell)
		return (0);
	i = 0;
	while (node->args[i])
	{
		expanded = expand_str(node->args[i],
				node->shell->exit_status, node->shell->env);
		if (!expanded)
			return (1);
		free(node->args[i]);
		node->args[i] = expanded;
		i++;
	}
	return (0);
}
