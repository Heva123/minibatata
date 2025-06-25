#include "minishell.h"
#include "signals.h"

const char *node_type_to_str(t_node_type type)
{
    switch (type)
    {
        case NODE_CMD: return "CMD";
        case NODE_REDIR_OUT: return "REDIR_OUT";
        case NODE_REDIR_IN: return "REDIR_IN";
        case NODE_APPEND: return "APPEND";
        case NODE_PIPE: return "PIPE";
        case NODE_HEREDOC: return "HEREDOC";
        default: return "UNKNOWN";
    }
}


static void print_args(char **args)
{
    int i = 0;

    if (!args)
    {
        printf("NULL");
        return;
    }

    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
}

void print_tree(t_node *node, int depth)
{
    if (!node)
        return;

    // Print right child first
    print_tree(node->right, depth + 1);

    // Indentation
    for (int i = 0; i < depth; i++)
        printf("        "); // 8 spaces per level for alignment

    // Print current node
    printf("└───> [%s]", node_type_to_str(node->type));

    if (node->type == NODE_CMD)
    {
        printf(" args: ");
        print_args(node->args);
    }
    else if (node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_IN ||
             node->type == NODE_APPEND || node->type == NODE_HEREDOC)
    {
        printf(" file: %s", node->filename ? node->filename : "NULL");
    }

    printf("\n");

    // Print left child
    print_tree(node->left, depth + 1);
}

int main(int argc, char **argv, char **envp)
{
    char    *prompt;
    t_node  *tree;
    char    **env_copy;
    int     i;

    (void)argc;
    (void)argv;

    // Initialize signal handling
    setup_shell_signals();

    // Copy environment variables
    i = 0;
    while (envp[i])
        i++;
    env_copy = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (envp[i])
    {
        env_copy[i] = ft_strdup(envp[i]);
        i++;
    }
    env_copy[i] = NULL;

    while (1)
    {
        prompt = readline("🍄 minishell$ ");
        if (!prompt)
        {
            ft_putstr_fd("exit\n", STDOUT_FILENO);
            break;
        }
        if (ft_strncmp(prompt, "exit", 5) == 0)
        {
            free(prompt);
            break;
        }
        add_history(prompt);
        tree = parse_prompt(prompt);
        tree->env = env_copy;
        print_tree(tree, 0);
        execute_tree(tree, envp);
        free(prompt);
    }
    
    // Free environment copy
    ft_free(env_copy);
    return (0);
}