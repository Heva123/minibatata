/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:59:54 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 19:00:35 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = copy_env(envp);
	shell->exit_status = 0;
	shell->is_running = true;
	update_pwd_vars(shell);
	return (shell);
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	ft_free_strarr(shell->env);
	free(shell->pwd);
	free(shell->oldpwd);
	free(shell);
}
