#include "minishell.h"

static int	ft_nlen(long n)
{
	int		i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	convert_to_string_recursive(long n, char *str, int *i)
{
	if (n > 9)
	{
		convert_to_string_recursive(n / 10, str, i);
		convert_to_string_recursive(n % 10, str, i);
	}
	else
		str[(*i)++] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nbr;

	nbr = n;
	str = malloc(sizeof(char) * (ft_nlen(nbr) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (nbr < 0)
	{
		str[i++] = '-';
		nbr *= -1;
	}
	convert_to_string_recursive(nbr, str, &i);
	str[i] = '\0';
	return (str);
}
