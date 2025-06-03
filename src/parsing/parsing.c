// // #include "../../minishell.h"


// // t_node	*parse_prompt(char *input)
// // {
// // 	t_node *node;

// // 	if ((node = parse_pipe(input)))
// // 		return node;
// // 	if ((node = parse_redir(input)))
// // 		return node;

// // 	node = new_node(NODE_CMD);
// // 	node->args = tokenize_input(input);
// // 	return node;
// // }

// #include "../../minishell.h"

// t_node *parse_prompt(char *input)
// {
//     t_node *node = NULL;
//     t_node *redir_node = NULL;
//     char *ptr = input;
//     int in_single = 0, in_double = 0;

//     if (!input)
//         return (NULL);

//     if ((node = parse_pipe(input)))
//         return node;

//     while (*ptr)
//     {
//         update_quote_state(*ptr, &in_single, &in_double);
//         if (!in_single && !in_double && (*ptr == '>' || *ptr == '<'))
//         {
//             redir_node = parse_redir(input);
//             if (redir_node)
//                 return redir_node;
//             break;
//         }
//         ptr++;
//     }

//     node = new_node(NODE_CMD);
//     if (!node)
//         return (NULL);
        
//     node->args = tokenize_input(input);
//     if (!node->args)
//     {
//         free(node);
//         return (NULL);
//     }
//     return node;
// }

#include "../../minishell.h"

static int	is_unquoted_operator(char *input, int i, int in_single, int in_double)
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


t_node *parse_prompt(char *input)
{
    int i = 0;
    int in_single = 0, in_double = 0;
    
    if (!input)
        return NULL;

    // First check for unquoted pipes
    while (input[i])
    {
        update_quote_state(input[i], &in_single, &in_double);
        if (is_unquoted_operator(input, i, in_single, in_double) && input[i] == '|')
        {
            input[i] = '\0';
            t_node *pipe_node = new_node(NODE_PIPE);
            if (!pipe_node)
                return NULL;
                
            pipe_node->left = parse_prompt(input);
            pipe_node->right = parse_prompt(&input[i+1]);
            return pipe_node;
        }
        i++;
    }

    // Then handle redirections (only unquoted ones)
    t_node *redir_node = parse_redir(input);
    if (redir_node)
        return redir_node;

    // If no pipes or redirections, it's a simple command
    t_node *cmd_node = new_node(NODE_CMD);
    if (!cmd_node)
        return NULL;
        
    cmd_node->args = tokenize_input(input);
    if (!cmd_node->args)
    {
        free(cmd_node);
        return NULL;
    }
    return cmd_node;
}