#include "../../minishell.h"

int	is_operator(const char *s)
{
	if (!s)
		return (0);
	if (*s == '|' || *s == '<' || *s == '>')
	{
		if ((s[0] == s[1]) && (s[0] == '<' || s[0] == '>'))
			return (2); // for << or >>
		return (1); // for | < >
	}
	return (0);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

void	update_quote_state(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	else if (c == '\"' && !(*in_single))
		*in_double = !(*in_double);
}

char	*strip_quotes(const char *token)
{
	int		in_single = 0, in_double = 0, i = 0, j = 0;
	char	*clean = malloc(strlen(token) + 1);
	if (!clean)
		return (NULL);
	while (token[i])
	{
		update_quote_state(token[i], &in_single, &in_double);
		if (!(token[i] == '\'' && !in_double) && !(token[i] == '\"' && !in_single))
			clean[j++] = token[i];
		i++;
	}
	clean[j] = '\0';
	return (clean);
}

char	**tokenize_input(const char *input)
{
	char	**tokens = malloc(sizeof(char *) * 1024); // adjust size as needed
	int		i = 0, start = 0, in_single = 0, in_double = 0, t = 0;

	while (input[i])
	{
		update_quote_state(input[i], &in_single, &in_double);
		if (!in_single && !in_double && (input[i] == ' ' || is_operator(&input[i])))
		{
			if (i > start)
				tokens[t++] = strip_quotes(strndup(&input[start], i - start));
			if (is_operator(&input[i]))
			{
				int op_len = is_operator(&input[i]);
				tokens[t++] = strndup(&input[i], op_len);
				i += op_len;
			}
			else
				i++;
			while (input[i] == ' ')
				i++;
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		tokens[t++] = strip_quotes(strndup(&input[start], i - start));
	tokens[t] = NULL;
	return (tokens);
}
