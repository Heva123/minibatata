#include "../../minishell.h"

int	is_operator(const char *s)
{
	if (!s)
		return (0);
	if (*s == '|' || *s == '<' || *s == '>')
	{
		if ((*s == '>' && *(s + 1) == '>')
			|| (*s == '<' && *(s + 1) == '<'))
			return (2);
		return (1);
	}
	return (0);
}

void	tokenize_helper(int *i, int *start, int *t,
			char **tokens, const char *input)
{
	int		op_len;
	char	*tmp;

	if (*i > *start)
	{
		tmp = ft_strndup(&input[*start], *i - *start);
		tokens[(*t)++] = process_quotes(tmp);
		free(tmp);
	}
	if (is_operator(&input[*i]))
	{
		op_len = is_operator(&input[*i]);
		tokens[(*t)++] = ft_strndup(&input[*i], op_len);
		*i += op_len;
		*start = *i;
		return ;
	}
	while (input[*i] == ' ')
		(*i)++;
	*start = *i;
}


void	add_token(int *t, char **tokens, const char *input, int start, int i)
{
	char	*token;

	token = ft_strndup(&input[start], i - start);
	tokens[(*t)++] = process_quotes(token);
	free(token);
}

char	**tokenize_input(const char *input)
{
	char	**tokens;
	int		i;
	int		start;
	int		t;
	int		quote_state[2];

	tokens = malloc(sizeof(char *) * 1024);
	i = 0;
	start = 0;
	t = 0;
	quote_state[0] = 0;
	quote_state[1] = 0;
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		update_quote_state(input[i], &quote_state[0], &quote_state[1]);
		if (!quote_state[0] && !quote_state[1] && (input[i] == ' '
				|| is_operator(&input[i])))
			tokenize_helper(&i, &start, &t, tokens, input);
		else
			i++;
	}
	if (i > start)
		add_token(&t, tokens, input, start, i);
	tokens[t] = NULL;
	return (tokens);
}

