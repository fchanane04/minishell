#include "lexer.h"
#include "../minishell.h"

static int	length(int n)
{
	int				len;
	unsigned int	b;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		b = n * -1;
	}
	else
		b = n;
	while (b > 0)
	{
		b /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*a;
	unsigned int	b;

	i = length(n);
	a = (char *)malloc ((i + 1) * sizeof(char));
	if (!a)
		return (0);
	a[i] = '\0';
	if (n == 0)
		a[0] = '0';
	if (n < 0)
	{
		a[0] = '-';
		b = n * -1;
	}
	else
		b = n;
	while (b > 0)
	{
		a[i - 1] = (b % 10) + '0';
		i--;
		b /= 10;
	}
	return (a);
}
