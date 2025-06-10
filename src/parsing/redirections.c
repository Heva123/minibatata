
#include "../../minishell.h"

t_node *parse_redir(char *prompt)
{
    char *ptr = prompt;
    char *last_redir = NULL;
    t_node_type redir_type = NODE_REDIR_OUT;
    int in_single = 0, in_double = 0;

    while (*ptr)
    {
        update_quote_state(*ptr, &in_single, &in_double);
        if (!in_single && !in_double && (*ptr == '>' || *ptr == '<'))
        {
            last_redir = ptr;
            if (*ptr == '>' && *(ptr + 1) == '>') {
                redir_type = NODE_APPEND;
                ptr++;
            }
            else if (*ptr == '<' && *(ptr + 1) == '<') {
                redir_type = NODE_HEREDOC;
                ptr++;
            }
            else if (*ptr == '>')
                redir_type = NODE_REDIR_OUT;
            else if (*ptr == '<')
                redir_type = NODE_REDIR_IN;
        }
        ptr++;
    }

    if (!last_redir)
        return NULL;

    // Split at the last redirection
    *last_redir = '\0';
    char *filename = last_redir + 1;
    if (redir_type == NODE_APPEND) 
        filename++;

    // Trim whitespace from filename
    while (*filename == ' ') 
        filename++;
    
    char *filename_end = filename;
    while (*filename_end && *filename_end != ' ') 
        filename_end++;
    *filename_end = '\0';

    t_node *node = new_node(redir_type);
    if (!node)
        return NULL;
        
    node->left = parse_prompt(prompt);
    node->filename = ft_strdup(filename);
    
    if (!node->filename)
    {
        free(node);
        return NULL;
    }
    
    return node;
}