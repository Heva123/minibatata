/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:13:03 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 19:14:03 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_quote_state(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	else if (c == '\"' && !(*in_single))
		*in_double = !(*in_double);
}

char	*process_quotes(const char *token)
{
	int		in_single;
	int		in_double;
	int		i;
	int		j;
	char	*clean;

	in_single = 0;
	in_double = 0;
	i = 0;
	j = 0;
	clean = malloc(ft_strlen(token) + 1);
	if (!clean)
		return (NULL);
	while (token[i])
	{
		update_quote_state(token[i], &in_single, &in_double);
		if (!(token[i] == '\'' && !in_double)
			&& !(token[i] == '\"' && !in_single))
			clean[j++] = token[i];
		i++;
	}
	clean[j] = '\0';
	return (clean);
}
