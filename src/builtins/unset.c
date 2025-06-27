/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:39:05 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 19:39:29 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_node *node, t_shell *shell)
{
	int	i;
	int	ret;

	if (!node || !node->args)
		return (shell->exit_status = 1);
	ret = 0;
	i = 1;
	while (node->args[i])
	{
		if (!is_valid_identifier(node->args[i]))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(node->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			ret = 1;
		}
		else if (unset_env_var(node->args[i], shell) != 0)
			ret = 1;
		i++;
	}
	return (shell->exit_status = ret);
}
