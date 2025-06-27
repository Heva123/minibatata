/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:49:13 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 18:51:53 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*result;
	int		i;
	int		j;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	*result = malloc(len1 + len2 + 1);
	i = 0;
	j = 0;
	if (!result)
		return (NULL);
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	while (j < len2)
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}
