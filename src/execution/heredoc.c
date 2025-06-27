// #include "minishell.h"

// static char	*read_heredoc_input(const char *delimiter)
// {
// 	char	*line;
// 	char	*input;
// 	char	*tmp;

// 	input = ft_strdup("");
// 	if (!input)
// 		return (NULL);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		tmp = input;
// 		input = ft_strjoin(input, line);
// 		free(tmp);
// 		free(line);
// 		if (!input)
// 			return (NULL);
// 		tmp = input;
// 		input = ft_strjoin(input, "\n");
// 		free(tmp);
// 		if (!input)
// 			return (NULL);
// 	}
// 	return (input);
// }

// static int	create_heredoc_file(const char *delimiter)
// {
// 	int		fd;
// 	char	*input;

// 	fd = open("/tmp/minishell_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd < 0)
// 	{
// 		perror("minishell: heredoc");
// 		return (-1);
// 	}
// 	input = read_heredoc_input(delimiter);
// 	if (!input)
// 	{
// 		close(fd);
// 		return (-1);
// 	}
// 	write(fd, input, ft_strlen(input));
// 	free(input);
// 	close(fd);
// 	fd = open("/tmp/minishell_heredoc", O_RDONLY);
// 	unlink("/tmp/minishell_heredoc");
// 	return (fd);
// }

// void	execute_heredoc(t_node *node, char **envp)
// {
// 	int	fd;
// 	int	saved_stdin;

// 	if (!node || !node->filename)
// 		return;
// 	fd = create_heredoc_file(node->filename);
// 	if (fd < 0)
// 		return;
// 	saved_stdin = dup(STDIN_FILENO);
// 	dup2(fd, STDIN_FILENO);
// 	close(fd);
// 	execute_tree(node->left, envp);
// 	dup2(saved_stdin, STDIN_FILENO);
// 	close(saved_stdin);
// }


#include "minishell.h"

static char	*read_heredoc_input(const char *delimiter, t_shell *shell)
{
	char	*line;
	char	*input;
	char	*tmp;

	input = ft_strdup("");
	if (!input)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break;
		}
		tmp = input;
		input = ft_strjoin(input, line);
		free(tmp);
		free(line);
		if (!input)
			return (NULL);
		tmp = input;
		input = ft_strjoin(input, "\n");
		free(tmp);
		if (!input)
			return (NULL);
	}
	(void)shell; // Can be used for signal handling if needed
	return (input);
}

static int	create_heredoc_file(const char *delimiter, t_shell *shell)
{
	int		fd;
	char	*input;

	fd = open("/tmp/minishell_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell: heredoc");
		shell->exit_status = 1;
		return (-1);
	}
	input = read_heredoc_input(delimiter, shell);
	if (!input)
	{
		close(fd);
		return (-1);
	}
	write(fd, input, ft_strlen(input));
	free(input);
	close(fd);
	fd = open("/tmp/minishell_heredoc", O_RDONLY);
	unlink("/tmp/minishell_heredoc");
	return (fd);
}

void	execute_heredoc(t_node *node, t_shell *shell)
{
	int	fd;
	int	saved_stdin;

	if (!node || !node->filename || !shell)
		return;
	
	fd = create_heredoc_file(node->filename, shell);
	if (fd < 0)
		return;
	
	saved_stdin = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	
	execute_tree(node->left, shell);
	
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}