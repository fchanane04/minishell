#include "lexer.h"
#include "../minishell.h"

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return(1);
	return(0);
}

char *handle_status(t_lexer *lexer)
{
	char	*s;
	
	s = NULL;
	lexer_advance(lexer);
	return(ft_itoa(*exit_status_setter(0x0)));
}

void	skip_alnum(t_lexer *lexer)
{
	while(ft_isalnum(lexer->c) == 1 && lexer->c != '\0')
		lexer_advance(lexer);
}

char	*dollar(t_lexer *lexer, t_token **token, int *flag)
{
	char	*s;
	char	c;

	s = NULL;
	c = lexer->line[lexer->i + 1];

	if (ft_is_digit(c) == 1)
	{
		lexer_advance(lexer);
		lexer_advance(lexer);//skip first digit(echo $234HOME ==> 234HOME)
		if (c == '0')
			return(strdup("minishell"));//print shell name (echo $0)
		return (NULL);
	}
	else if (lexer->c == '$' && ft_isalnum(c) != 1  && c != '$')//whitout expand
	{
		lexer_advance(lexer);//skip '$'
		if (lexer->c == '?')
			return(handle_status(lexer));
		if (lexer->c == '_')
		{
			skip(lexer, '_');
			skip_alnum(lexer);
			return (NULL);
		}
		return(get_char_as_string('$'));
	}
	else if (lexer->c == '$' && (lexer->line[lexer->i + 1] == '"' || lexer->line[lexer->i + 1] == '\''))
	{
		lexer_advance(lexer);
		return (NULL);
	}
	else if (lexer->c == '$' && red_or_pipe(lexer->line[lexer->i + 1]) != 1)
		return (expand_dollar(lexer, token, flag));
	return (NULL); 
}
