#include "lexer.h"
#include "../minishell.h"

// ' '      space 
// '\t'     horizontal tab 
// '\n'     newline
// '\v'     vertical tab 
// '\f'     form feed 
// '\r'     carriage return

int	is_whitespaces(char c)
{
	if (c == ' ' || c == '\t')
		return(0);
	return(1);
}

int	is_space(char *expand)
{
	int	i;

	i = 0;
	if (expand == NULL)
		return (1);
	while (expand[i] != '\0')
	{
		if (is_whitespaces(expand[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int count_word(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

char	*handle_spaces(char *expand,t_token **token,int *flag)
{
	char	**a;
	int		count;
	int		i;

	i = 0;
	a = ft_split(expand, ' ');//tab
	count = count_word(a);
	while (i < count - 1)
	{
		add_token_back(token, init_token(WORD, a[i], flag, 1));
		i++;
	}
	return(a[i]);
}
