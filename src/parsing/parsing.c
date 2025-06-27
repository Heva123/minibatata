/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:15:22 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 19:16:47 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast(t_node *node)
{
	if (!node)
		return ;
	if (node->args)
		ft_free(node->args);
	if (node->filename)
		free(node->filename);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

static int	is_unquoted_operator(char *input, int i,
	int in_single, int in_double)
{
	int	j;

	if (in_single || in_double)
		return (0);
	if (input[i] == '|' || input[i] == '>' || input[i] == '<')
	{
		j = i;
		while (j > 0 && input[j - 1] == '\\')
			j--;
		if (((i - j) % 2) == 0)
			return (1);
	}
	return (0);
}

static t_node	*handle_pipe_or_redir(char *input)
{
	int		i;
	int		in_single;
	int		in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (input[i])
	{
		update_quote_state(input[i], &in_single, &in_double);
		if (is_unquoted_operator(input, i, in_single, in_double)
			&& input[i] == '|')
		{
			input[i] = '\0';
			t_node *pipe = new_node(NODE_PIPE);
			if (!pipe)
				return (NULL);
			pipe->left = parse_prompt(input);
			pipe->right = parse_prompt(&input[i + 1]);
			return (pipe);
		}
		i++;
	}
	return (parse_redir(input));
}

t_node	*parse_prompt(char *input)
{
	t_node	*node;

	if (!input)
		return (NULL);
	node = handle_pipe_or_redir(input);
	if (node)
		return (node);
	node = new_node(NODE_CMD);
	if (!node)
		return (NULL);
	node->args = tokenize_input(input);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	return (node);
}
