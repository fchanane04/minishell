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

void	add_app(t_lexer *lexer, t_token **token, int *flag)
{
	char *s;

	s = NULL;
	if (lexer->c == '>')
	{
		s = strdup(">>");
		add_token_back(token, init_token(APP, s, flag));
	}
	lexer_advance(lexer);
}

void	add_red_and_pipe(t_lexer *lexer, t_token **token, int *flag)
{
	char	*s;

	s = NULL;
	s = get_char_as_string(lexer->c);
    if (lexer->c == '>' && lexer->line[lexer->i + 1] != '>')
			add_token_back(token, init_token(R_RED, s, flag));// add > 
    else if (lexer->c == '<' && lexer->line[lexer->i + 1] != '<')
		add_token_back(token, init_token(L_RED, s, flag));//add <
	else if (lexer->c == '>' && lexer->line[lexer->i + 1] == '>')
        add_app(lexer, token, flag);//>>
    else if (lexer->c == '<' && lexer->line[lexer->i + 1] == '<')
	{
		add_herdoc(lexer, token, flag);
		return;
	}
    else if (lexer->c == '|')
		add_token_back(token, init_token(PIPE, s, flag));
    lexer_advance(lexer);
}

void	add_word(t_lexer *lexer, t_token **token, int *flag, char **envp)
{
	char	*s;
	char	*str;

	s = NULL;
	str = NULL;
	while (lexer->c != ' ' && lexer->c != '\0' && red_or_pipe(lexer->c) != 1 )
	{
		if (lexer->c == '"' || lexer->c == '\'')
			s = get_str_inside_quotes(lexer, envp);
		else if (lexer->c == '$')
			s = expand_dollar(lexer, envp);
		else
			s = get_str(lexer);
		if (s != NULL)
		{
			str = ft_strjoin(str, s);//pour gerer ce genre de cas : ech""o ==> s = NULL
			ft_free(s);
		}
	}
	add_token_back(token, init_token(WORD, str, flag));
}

t_token	*get_token(t_lexer *lexer, char **envp)
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
			add_word(lexer, &token, &flag, envp);
    }
	return(token);
 }
