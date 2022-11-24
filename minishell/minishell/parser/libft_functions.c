#include "../lexer/lexer.h"
#include "../minishell.h"

void    ft_free(char *str)
{
	if (str != NULL)
	{
    	free(str);
    	str = NULL;//ma3nd rbha hta ma3na 
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

	s = NULL;
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
	if (s1 == NULL && s2 != NULL)
		return (strdup(s2));
	else if (s1 == NULL)
		return(NULL);
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