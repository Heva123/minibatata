
#include "minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
	{
		return (1);
	}
	return (0);
}

int ft_isnumber(const char *str)
{
    int i;

    if (!str || !*str)
        return (0);
    
    i = 0;
    // Handle optional sign
    if (str[i] == '+' || str[i] == '-')
        i++;
    
    // Check remaining characters are digits
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    
    return (1);
}