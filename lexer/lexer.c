/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:30:32 by nel-brig          #+#    #+#             */
/*   Updated: 2022/11/25 16:30:34 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		free(s);
		s = NULL;
		lexer_advance(lexer);
	}
	return (str);
}

void	add_app(t_lexer *lexer, t_token **token, char *str)
{
	char	*s;

	s = NULL;
	free(str);
	str = NULL;
	if (lexer->c == '>')
	{
		s = strdup(">>");
		add_token_back(token, init_token(APP, s));
	}
	lexer_advance(lexer);
}

void	add_red_and_pipe(t_lexer *lexer, t_token **token)
{
	char	*s;

	s = NULL;
	s = get_char_as_string(lexer->c);
	if (lexer->c == '>' && lexer->line[lexer->i + 1] != '>')
		add_token_back(token, init_token(R_RED, s));
	else if (lexer->c == '<' && lexer->line[lexer->i + 1] != '<')
		add_token_back(token, init_token(L_RED, s));
	else if (lexer->c == '>' && lexer->line[lexer->i + 1] == '>')
		add_app(lexer, token, s);
	else if (lexer->c == '<' && lexer->line[lexer->i + 1] == '<')
	{
		add_herdoc(lexer, token);
		free(s);
		s = NULL;
		return ;
	}
	else if (lexer->c == '|')
		add_token_back(token, init_token(PIPE, s));
	lexer_advance(lexer);
}

char	*add_word(t_lexer *lexer, t_token **token)
{
	char	*s;
	char	*str;

	s = NULL;
	str = NULL;
	while ((is_space(lexer->c) != 0) && lexer->c != '\0'
		&& red_or_pipe(lexer->c) != 1)
	{
		if (is_quote(lexer->c) == 0)
		{
			s = get_str_inside_quotes(lexer, token);
			if (s == NULL && (is_space(lexer->c) == 0 || lexer->c == '\0'))
			{
				s = get_char_as_string('\0');
				str = ft_strjoin(str, s);
				ft_free(&s);
				continue ;
			}
		}
		else
			expand_or_string(lexer, token, &str, &s);
		if (s != NULL)
			str = join_and_free(str, &s);
	}
	return (str);
}

t_token	*get_token(t_lexer *lexer)
{
	t_token	*token;
	char	*str;

	token = NULL;
	str = NULL;
	while (lexer->c != '\0')
	{
		ft_skip_whitespaces(lexer);
		if (red_or_pipe(lexer->c) == 1)
			add_red_and_pipe(lexer, &token);
		else if (red_or_pipe(lexer->c) != 1)
		{
			str = add_word(lexer, &token);
			if (str != NULL)
				add_token_back(&token, init_token(WORD, str));
		}
	}
	return (token);
}
