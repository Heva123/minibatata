/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:53:05 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 18:53:06 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((s1[i] || s2[j]) && i < n)
	{
		if (s1[i] != s2[j])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[j]);
		}
		i++;
		j++;
	}
	return (0);
}
