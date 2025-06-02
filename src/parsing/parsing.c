#include "../../minishell.h"


t_node	*parse_prompt(char *input)
{
	t_node *node;

	if ((node = parse_pipe(input)))
		return node;
	if ((node = parse_redir(input)))
		return node;

	node = new_node(NODE_CMD);
	node->args = tokenize_input(input);
	return node;
}
