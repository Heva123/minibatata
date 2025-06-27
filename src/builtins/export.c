/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:40:12 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 19:42:13 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int print_exported_vars(char **env)
{
	int		i;
	char	**sorted_env;

	i = 0;
	while (env[i])
		i++;
	sorted_env = malloc(sizeof(char *) * (i + 1));
	if (!sorted_env)
		return (1);
	i = 0;
	while (env[i])
	{
		sorted_env[i] = ft_strdup(env[i]);
		i++;
	}
	sorted_env[i] = NULL;
	ft_sort_strarr(sorted_env);
	i = 0;
	while (sorted_env[i])
	{
		char *equal = ft_strchr(sorted_env[i], '=');
		if (equal)
		{
			*equal = '\0';
			printf("declare -x %s=\"%s\"\n", sorted_env[i], equal + 1);
		}
		else
			printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	ft_free(sorted_env);
	return (0);
}

int	ft_export(t_node *node, t_shell *shell)
{
	int		i;
	int		ret;
	char	*equal_sign;
	char	*var;
	char	*value;

	if (!node || !node->args)
		return (shell->exit_status = 1);
	if (!node->args[1])
		return (shell->exit_status = print_exported_vars(shell->env));
	ret = 0;
	i = 1;
	while (node->args[i])
	{
		if (!is_valid_identifier(node->args[i]))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(node->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			ret = 1;
			i++;
			continue ;
		}
		equal_sign = ft_strchr(node->args[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			var = node->args[i];
			value = equal_sign + 1;
			if (set_env_var(var, value, shell) != 0)
				ret = 1;
			*equal_sign = '=';
		}
		i++;
	}
	return (shell->exit_status = ret);
}
