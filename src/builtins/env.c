/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:43:08 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 19:43:39 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_node *node, t_shell *shell)
{
	int	i;

	(void)node;
	if (!shell->env)
		return (shell->exit_status = 1);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
			printf("%s\n", shell->env[i]);
		i++;
	}
	return (shell->exit_status = 0);
}
