#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	t_node	*tree;

	(void)argc;
	(void)argv;

	while (1)
	{
		prompt = readline("🍄 minishell$ ");
		if (!prompt)
			break;
		if (ft_strncmp(prompt, "exit", 4) == 0)
		{
			free(prompt);
			break;
		}
		add_history(prompt);
		tree = parse_prompt(prompt);
		execute_tree(tree, envp);
		free(prompt);
	}
	return (0);
}