/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:14:12 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 19:16:35 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse_pipe(char *prompt)
{
	char	*pipe_pos;

	pipe_pos = ft_strchr(prompt, '|');
	if (pipe_pos)
	{
		*pipe_pos = '\0';
		t_node *node = new_node(NODE_PIPE);
		node->left = parse_prompt(prompt);
		node->right = parse_prompt(pipe_pos + 1);
		return (node);
	}
	return (NULL);
}
