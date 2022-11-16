#include "../lexer/lexer.h"
#include "../minishell.h"

void    ft_free(char *str)
{
	if (str != NULL)
	{
    	free(str);
    	str = NULL;
	}
}

int	ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return(i);
}

char	*get_char_as_string(char c)
{
    char *s;

    s = malloc(sizeof(char) * 2);
    if (!s)
        exit(EXIT_FAILURE);
    s[0] = c;
    s[1] = '\0';
    return (s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*a;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2)
		return(NULL);
	if (!s1)
	{
		a = strdup(s2);
		return (a);
	}
	a = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (a == NULL)
		return (0);
	while (s1[i])
	{
		a[i] = s1[i];
		i++;
    }
	while (s2[j])
	{
		a[i] = s2[j];
		i++;
		j++;
	}
	a[i] = '\0';
    free(s1);
	return (a);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}