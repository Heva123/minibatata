#include "../../minishell.h"


int	ft_strlen(const char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}