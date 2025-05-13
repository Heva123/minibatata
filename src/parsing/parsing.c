#include "../../minishell.h"


t_node	*parse_prompt(char *prompt)
{
	t_node *node;

	if ((node = parse_pipe(prompt)))
		return node;
	if ((node = parse_redir(prompt)))
		return node;

	node = new_node(NODE_CMD);
	node->args = ft_split(prompt, ' ');
	return node;
}