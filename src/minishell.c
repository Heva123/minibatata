#include "minishell.h"
#include "signals.h"

// const char *node_type_to_str(t_node_type type)
// {
//     switch (type)
//     {
//         case NODE_CMD: return "CMD";
//         case NODE_REDIR_OUT: return "REDIR_OUT";
//         case NODE_REDIR_IN: return "REDIR_IN";
//         case NODE_APPEND: return "APPEND";
//         case NODE_PIPE: return "PIPE";
//         case NODE_HEREDOC: return "HEREDOC";
//         default: return "UNKNOWN";
//     }
// }


// static void print_args(char **args)
// {
//     int i = 0;

//     if (!args)
//     {
//         printf("NULL");
//         return;
//     }

//     while (args[i])
//     {
//         printf("%s", args[i]);
//         if (args[i + 1])
//             printf(" ");
//         i++;
//     }
// }

// void print_tree(t_node *node, int depth)
// {
//     if (!node)
//         return;

//     // Print right child first
//     print_tree(node->right, depth + 1);

//     // Indentation
//     for (int i = 0; i < depth; i++)
//         printf("        "); // 8 spaces per level for alignment

//     // Print current node
//     printf("└───> [%s]", node_type_to_str(node->type));

//     if (node->type == NODE_CMD)
//     {
//         printf(" args: ");
//         print_args(node->args);
//     }
//     else if (node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_IN ||
//              node->type == NODE_APPEND || node->type == NODE_HEREDOC)
//     {
//         printf(" file: %s", node->filename ? node->filename : "NULL");
//     }

//     printf("\n");

//     // Print left child
//     print_tree(node->left, depth + 1);
// }
int main(int argc, char **argv, char **envp)
{
    t_shell *shell = init_shell(envp);
    char    *input;
    t_node  *ast;

    (void)argc;
    (void)argv;
    
    if (!shell)
        return (1);
    
    while (shell->is_running)
    {
        setup_shell_signals();
        input = readline("🍄 minishell$ ");
        if (!input)
        {
            ft_putstr_fd("exit\n", STDOUT_FILENO);
            break;
        }
        
        if (*input)
        {
            add_history(input);
            ast = parse_prompt(input);
            if (ast)
            {
                ast->shell = shell;
                execute_tree(ast, shell);
                free_ast(ast);
            }
        }
        free(input);
    }
    
    cleanup_shell(shell);
    return (shell->exit_status);
}