// #include "../../minishell.h"


// t_node	*parse_prompt(char *input)
// {
// 	t_node *node;

// 	if ((node = parse_pipe(input)))
// 		return node;
// 	if ((node = parse_redir(input)))
// 		return node;

// 	node = new_node(NODE_CMD);
// 	node->args = tokenize_input(input);
// 	return node;
// }

#include "../../minishell.h"

t_node *parse_prompt(char *input)
{
    t_node *node = NULL;
    t_node *redir_node = NULL;
    char *ptr = input;
    int in_single = 0, in_double = 0;

    if (!input)
        return (NULL);

    if ((node = parse_pipe(input)))
        return node;

    while (*ptr)
    {
        update_quote_state(*ptr, &in_single, &in_double);
        if (!in_single && !in_double && (*ptr == '>' || *ptr == '<'))
        {
            redir_node = parse_redir(input);
            if (redir_node)
                return redir_node;
            break;
        }
        ptr++;
    }

    node = new_node(NODE_CMD);
    if (!node)
        return (NULL);
        
    node->args = tokenize_input(input);
    if (!node->args)
    {
        free(node);
        return (NULL);
    }
    return node;
}