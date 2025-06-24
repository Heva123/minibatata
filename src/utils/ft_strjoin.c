
#include "minishell.h"


char	*ft_strjoin(char const *s1, char const *s2)
{
	int	len1 = ft_strlen(s1);
	int	len2 = ft_strlen(s2);
	char	*result = malloc(len1 + len2 + 1);
	int	i = 0, j = 0;

	if (!result)
		return NULL;
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
	return result;
}