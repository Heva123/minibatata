
#include "../../minishell.h"

static void update_redir_type(char **ptr, t_node_type *redir_type)
{
    if (**ptr == '>' && *(*ptr + 1) == '>')
    {
        *redir_type = NODE_APPEND;
        (*ptr)++;
    }
    else if (**ptr == '<' && *(*ptr + 1) == '<')
    {
        *redir_type = NODE_HEREDOC;
        (*ptr)++;
    }
    else if (**ptr == '>')
        *redir_type = NODE_REDIR_OUT;
    else if (**ptr == '<')
        *redir_type = NODE_REDIR_IN;
}

static char *find_last_redir(char *prompt, t_node_type *redir_type)
{
    char *ptr = prompt;
    char *last_redir = NULL;
    int in_single = 0, in_double = 0;

    while (*ptr)
    {
        update_quote_state(*ptr, &in_single, &in_double);
        if (!in_single && !in_double && (*ptr == '>' || *ptr == '<'))
        {
            last_redir = ptr;
            update_redir_type(&ptr, redir_type);
        }
        ptr++;
    }
    return last_redir;
}

static char *skip_spaces(char *str)
{
    while (*str == ' ')
        str++;
    return str;
}

static char *extract_quoted_filename(char *filename)
{
    char quote = *filename++;
    char *start = filename;

    while (*filename && *filename != quote)
        filename++;
    *filename = '\0';
    return start;
}

static char *extract_unquoted_filename(char *filename)
{
    char *start = filename;

    while (*filename && *filename != ' ')
    {
        if (*filename == '.')
        {
            while (*filename && *filename != ' ')
                filename++;
            break;
        }
        filename++;
    }
    *filename = '\0';
    return start;
}

static char *extract_filename(char *redir_ptr, t_node_type redir_type)
{
    char *filename;

    redir_ptr[0] = '\0';  // terminate prompt before redir
    filename = redir_ptr + 1;

    if (redir_type == NODE_APPEND || redir_type == NODE_HEREDOC)
        filename++;

    filename = skip_spaces(filename);

    if (*filename == '\'' || *filename == '\"')
        return extract_quoted_filename(filename);

    return extract_unquoted_filename(filename);
}

t_node *parse_redir(char *prompt)
{
    t_node_type redir_type = NODE_REDIR_OUT;
    char *last_redir = find_last_redir(prompt, &redir_type);
    t_node *node;
    char *filename;

    if (!last_redir)
        return NULL;

    filename = extract_filename(last_redir, redir_type);
    node = new_node(redir_type);
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

