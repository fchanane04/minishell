#include "lexer.h"
#include "../minishell.h"

char	*get_string_inside_quotes(t_lexer *lexer)
{
	char	c;
	char	*s;
	char	*str;

	c = lexer->c;
	s = NULL;
	str = NULL;
	lexer_advance(lexer);
	while (lexer->c != c)
	{
		s = get_char_as_string(lexer->c);
		str = ft_strjoin(str, s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return(str);
}

char *get_string(t_lexer *lexer)
{
	char	*s;
	char	*str;

	s = NULL;
	str = NULL;
	while (lexer->c != ' ' && lexer->c != '\0' && lexer->c != '"' && lexer->c != '\'' && red_or_pipe(lexer->c) != 1)
	{
		s = get_char_as_string(lexer->c);
		str = ft_strjoin(str, s);
		ft_free(s);
		lexer_advance(lexer);
	}
	return(str);
}

void	add_herdoc_as_token(t_token **token, int *flag)
{
	char	*s;

	s = NULL;
	s = ft_strdup("<<");
	add_token_back(token, init_token(DEL, s, flag));
}

void	add_herdoc(t_lexer *lexer, t_token **token, int *flag)
{
	char *s;
	char *str;

	s = NULL;
	str = NULL;
	lexer_advance(lexer);
	lexer_advance(lexer);
	ft_skip_whitespaces(lexer);
	add_herdoc_as_token(token, flag);
	while (lexer->c != ' ' && lexer->c != '\0' && red_or_pipe(lexer->c) != 1)
	{
		if (lexer->c == '\'' || lexer->c == '"')
			s = get_string_inside_quotes(lexer);
		else
			s = get_string(lexer);
		if(s != NULL)
			str = ft_strjoin(str, s);
	}
	if (str != NULL)
	{
		add_token_back(token, init_token(WORD, str, flag));
		// ft_free(str);
	}
}