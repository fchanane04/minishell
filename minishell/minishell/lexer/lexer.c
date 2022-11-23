#include "lexer.h"
#include "../minishell.h"

char	*get_str(t_lexer *lexer)
{
	char	*s;
	char	*str;

	s = NULL;
	str = NULL;
	while (special_characters(lexer->c) != 1)
    {
		s = get_char_as_string(lexer->c);
        str = ft_strjoin(str, s);
		ft_free(s);
        lexer_advance(lexer);
	}
	return(str);
}

void	add_app(t_lexer *lexer, t_token **token,char *str ,int *flag)
{
	char *s;

	s = NULL;
	ft_free(str);
	if (lexer->c == '>')
	{
		s = strdup(">>");
		add_token_back(token, init_token(APP, s, flag, -1));
	}
	lexer_advance(lexer);
}

void	add_red_and_pipe(t_lexer *lexer, t_token **token, int *flag)
{
	char	*s;

	s = NULL;
	s = get_char_as_string(lexer->c);
    if (lexer->c == '>' && lexer->line[lexer->i + 1] != '>')
			add_token_back(token, init_token(R_RED, s, flag, -1));// add > 
    else if (lexer->c == '<' && lexer->line[lexer->i + 1] != '<')
		add_token_back(token, init_token(L_RED, s, flag, -1));//add <
	else if (lexer->c == '>' && lexer->line[lexer->i + 1] == '>')
        add_app(lexer, token, s,flag);//>>
    else if (lexer->c == '<' && lexer->line[lexer->i + 1] == '<')
	{
		add_herdoc(lexer, token,flag);
		ft_free(s);
		return;
	}
    else if (lexer->c == '|')
		add_token_back(token, init_token(PIPE, s, flag, -1));
    lexer_advance(lexer);
}

void	add_word(t_lexer *lexer, t_token **token, int *flag)
{
	char	*s;
	char	*str;

	s = NULL;
	str = NULL;
	while (lexer->c != ' ' && lexer->c != '\0' && red_or_pipe(lexer->c) != 1 )
	{
		if (lexer->c == '"' || lexer->c == '\'')
			s = get_str_inside_quotes(lexer, token, flag);
		else if (lexer->c == '$' && (lexer->line[lexer->i + 1] == '"' || lexer->line[lexer->i + 1]  == '\''))
			lexer_advance(lexer);
		else if (lexer->c == '$')
			s = dollar(lexer, token, flag);
		else
			s = get_str(lexer);
		if (s != NULL)
		{
			str = ft_strjoin(str, s);
			ft_free(s);
		}
	}
	if (str != NULL)
		add_token_back(token, init_token(WORD, str, flag, -1));
}

t_token	*get_token(t_lexer *lexer)
{
	int		flag;
	t_token	*token;

	token = NULL;
	flag = 0;// to check if it's a new line for token->index
	while (lexer->c != '\0')
	{
		ft_skip_whitespaces(lexer);
		if (red_or_pipe(lexer->c) == 1)
			add_red_and_pipe(lexer, &token, &flag);
        else if (red_or_pipe(lexer->c) != 1)
			add_word(lexer, &token, &flag);
    }
	return(token);
 }
