#include "lexer.h"
#include "../minishell.h"

void	skip(t_lexer *lexer, char c)
{
	while (lexer->c == c)
		lexer_advance(lexer);
}

int	check_dollar(t_lexer *lexer)
{
	int	count;
	int	i;

	count = 1;
	i = 1;
	while (lexer->line[lexer->i + i] == '$')
	{
		i++;
		count++;
	}
	return(count);
}

char	*get_dollar(int	size, t_lexer *lexer)
{
	char	*s;
	int		i;

	i = 0;
	if (size == 0)
		return(NULL);
	s = malloc(sizeof(char) * (size + 1));
	if (!s)
		exit(EXIT_FAILURE);
	while (i < size)
	{
		s[i++] = lexer->c;
		lexer_advance(lexer);
	}
	s[i] = '\0';
	return(s);
}

char	*whithout_expand(t_lexer *lexer)
{
	char	*s;
	char	*str;

	s = NULL;
	str = NULL;
	str = get_dollar(check_dollar(lexer), lexer);
	skip(lexer, '$');
	while (special_characters(lexer->c) != 1 && ft_isalnum(lexer->c))
	{
		s = get_char_as_string(lexer->c);
		str = ft_strjoin(str, s);
		free(s);
		lexer_advance(lexer);
	}
	return(str);
}

char	*expand_dollar(t_lexer *lexer, t_token **token, int *flag)
{
	char	*s;
	char	*str;
	char	*expand;

	s = NULL;
	str = NULL;
	expand = NULL;
	if (check_dollar(lexer) % 2 == 0)
		return(whithout_expand(lexer));
	if (check_dollar(lexer) != 1)
		return(get_dollar(check_dollar(lexer) - 1, lexer));
	lexer_advance(lexer);//skip dollar;
	if (lexer->c == ' ' || lexer->c == '\0')
		return(get_char_as_string('$'));
	while (special_characters(lexer->c) != 1 && ft_isalnum(lexer->c))
	{
		s = get_char_as_string(lexer->c);
		str = ft_strjoin(str, s);
		ft_free(s);
		lexer_advance(lexer);
	}
	if (lexer->c == '_')
	{
		free(str);
		skip(lexer, '_');
		return (NULL);
	}
	expand = get_env(str);
	if (is_space(expand) == 0)
		return(handle_spaces(expand, token, flag));
	return(expand);
}

  