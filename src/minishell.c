/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:54:54 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 18:57:44 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*input;
	t_node	*ast;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
		return (1);
	while (shell->is_running)
	{
		setup_shell_signals();
		input = readline("🍄 minishell$ ");
		if (!input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (*input)
		{
			add_history(input);
			ast = parse_prompt(input);
			if (ast)
			{
				ast->shell = shell;
				execute_tree(ast, shell);
				free_ast(ast);
			}
		}
		free(input);
	}
	cleanup_shell(shell);
	return (shell->exit_status);
}
