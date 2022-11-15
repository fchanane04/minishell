#include "lexer.h"
#include "../minishell.h"

t_lexer *init_lexer(char *line)
{
    t_lexer *lexer = malloc(sizeof(t_lexer));
    if (!lexer)
        exit(EXIT_FAILURE);
    lexer->line = strdup(line);
    lexer->i = 0;
    lexer->c = lexer->line[lexer->i];
	return(lexer);
}

int red_or_pipe(char c)
{
    if (c == '>' || c == '<' || c == '|')
        return (1);
    return (0);
}

int special_characters(char c)
{
	if (red_or_pipe(c) != 1)
	{
		if (c != '\0' && c != ' ' && c != '"' && c != '\'' && c != '$')
			return(0);
	}
	return(1);
}

void lexer_advance(t_lexer *lexer)
{
    if (lexer->i < ft_strlen(lexer->line))
    {
        lexer->i += 1;
        lexer->c = lexer->line[lexer->i];
    }
}

void	ft_skip_whitespaces(t_lexer *lexer)
{
	while (lexer->c == ' ')
		lexer_advance(lexer);
}

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
        lexer_advance(lexer);
	}
	return(str);
}

void	add_del_app(t_lexer *lexer, t_token **token, int *flag)
{
	char *s;

	s = NULL;
	if (lexer->c == '>')
	{
		s = strdup(">>");
		add_token_back(token, init_token(APP, s, flag));
	}
	else if (lexer->c == '<')
	{
		s = strdup("<<");
		add_token_back(token, init_token(DEL, s, flag));
	}
	lexer_advance(lexer);
}

void	add_red_and_check_pipe(t_token **token, t_lexer *lexer, int *flag, char *s)
{
	add_token_back(token, init_token(R_RED, s, flag));
	if (lexer->line[lexer->i + 1] == '|')
		lexer_advance(lexer);
	else if (lexer->line[lexer->i + 1] == ' ')
	{
		ft_skip_whitespaces(lexer);
		if (lexer->c == '|')
			add_token_back(token, init_token(PIPE, s, flag));
	}
}

char    *get_env(char *str, char **envp)
{
    int i;
    char *s;

    i = 0;
    while(envp[i] != NULL)
    {
        if (strncmp(envp[i], str, ft_strlen(str)) == 0)
        {
            s = strdup(envp[i] + ft_strlen(str) + 1);
            return(s);
        }
        i++;
    }
	ft_free(str);
	return(NULL);
}

char *expand(t_lexer *lexer, char **envp)
{
	char	*s;
	char	*str;
	char	*expand;

	s = NULL;
	str = NULL;
	expand = NULL;
	while (special_characters(lexer->c) != 1 && ft_isalnum(lexer->c))
	{
		s = get_char_as_string(lexer->c);
		str = ft_strjoin(str, s);
		lexer_advance(lexer);
	}
	expand = get_env(str, envp);
	while (lexer->c == '_')
	{
		lexer_advance(lexer);
		expand = NULL;
	}
	return(expand);
}

char	*expand_dollar(t_lexer *lexer, char **envp)
{
	char	*str;
	char	*s;
	char	*expand;

	str = NULL;
	s = NULL;
	lexer_advance(lexer);//skip $
	while (special_characters(lexer->c) != 1 && ft_isalnum(lexer->c))
	{
		s = get_char_as_string(lexer->c);
		str = ft_strjoin(str, s);
		lexer_advance(lexer);
	}
	expand = get_env(str, envp);
	while (lexer->c == '_')
	{
		lexer_advance(lexer);
		expand = NULL;
	}
	return(expand);
	// str = expand(lexer, envp);
}

void	add_red_and_pipe(t_lexer *lexer, t_token **token, int *flag)
{
	char	*s;
	char	*str;

	s = NULL;
	s = get_char_as_string(lexer->c);
    if (lexer->c == '>' && lexer->line[lexer->i + 1] != '>')
		add_red_and_check_pipe(token, lexer, flag, s);
    else if (lexer->c == '<' && lexer->line[lexer->i + 1] != '<')
	{
		if (lexer->line[lexer->i + 1] == ' ' && lexer->line[lexer->i + 2] == '>')
		{
			str = get_char_as_string('>');
			error_msg(ERROR_MSG, str);
		}
		add_token_back(token, init_token(L_RED, s, flag));
	}
	else if (lexer->c == '>' && lexer->line[lexer->i + 1] == '>')
        add_del_app(lexer, token, flag);
    else if (lexer->c == '<' && lexer->line[lexer->i + 1] == '<')
        add_del_app(lexer, token, flag);
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
		if (s != NULL)//pour gerer ce genre de cas : ech""o ==> s = NULL
			str = ft_strjoin(str, s);
	}
	if (str != NULL)
	{
		add_token_back(token, init_token(WORD, str, flag));
		free(str);
		str = NULL;
	}
}

t_token	*get_token(t_lexer *lexer, char **envp)
{
	int		flag;
	t_token *token;

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
