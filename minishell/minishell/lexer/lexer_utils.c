#include "lexer.h"
#include "../minishell.h"

t_lexer	*init_lexer(char *line)
{
    t_lexer	*lexer = malloc(sizeof(t_lexer));
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

void	lexer_advance(t_lexer *lexer)
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