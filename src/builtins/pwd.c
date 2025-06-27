/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:39:38 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 19:40:06 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_node *node, t_shell *shell)
{
	char	cwd[PATH_MAX];

	(void)node;
	(void)shell;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("minishell: pwd");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
