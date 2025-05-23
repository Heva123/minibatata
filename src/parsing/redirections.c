#include "../../minishell.h"


t_node *parse_redir(char *prompt)
{
    char    *copy = ft_strdup(prompt);
    char    *ptr = copy;
    char    *last_redir = NULL;
    char    *cmd = NULL;
    t_node_type redir_type = NODE_REDIR_OUT;

    // 1. Find last redirection position
    while (*ptr)
    {
        if (*ptr == '>' || *ptr == '<')
        {
            last_redir = ptr;
            // Check for >>
            if (*ptr == '>' && *(ptr + 1) == '>')
            {
                redir_type = NODE_APPEND;
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
    {
        free(copy);
        return (NULL);
    }

    // 2. Duplicate full command before any redirection
    int cut_index = last_redir - copy;
    cmd = strndup(copy, cut_index);

    // 3. Get filename (from last redir)
    char *file_ptr = last_redir;
    if (redir_type == NODE_APPEND) file_ptr++; 
    file_ptr++; 
    while (*file_ptr == ' ') file_ptr++;
    char *file_end = file_ptr;
    while (*file_end && *file_end != ' ' && *file_end != '>' && *file_end != '<') file_end++;
    char *filename = strndup(file_ptr, file_end - file_ptr);

  
    t_node *node = new_node(redir_type);
    node->left = parse_prompt(cmd);
    node->filename = filename;

    free(cmd);
    free(copy);
    return (node);
}