/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:29:37 by nel-brig          #+#    #+#             */
/*   Updated: 2022/12/02 22:29:38 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

char	*status_handler(t_lexer *lexer_exp)
{
	lexer_advance(lexer_exp);
	if (lexer_exp->c == '?')
		return (handle_status(lexer_exp));
	return (get_char_as_string('$'));
}

char	*expanded_word(t_lexer *lexer_exp)
{
	char	*str;
	char	*expand;

	str = NULL;
	expand = NULL;
	lexer_advance(lexer_exp);
	str = get_string_to_expand(lexer_exp);
	expand = get_env(str);
	free(str);
	return (expand);
}

char	*expand(t_lexer *lexer_exp)
{
	char	c;
	char	*dollar;

	dollar = NULL;
	c = lexer_exp->line[lexer_exp->i + 1];
	if (ft_is_digit(c) == 1)
		return (skip_first_digit(lexer_exp));
	else if (lexer_exp->c == '$' && ft_isalnum(c) != 1 && c != '_' && c != '$')
		return (status_handler(lexer_exp));
	else if (red_or_pipe(c) != 1)
	{
		if (check_dollar(lexer_exp) % 2 == 0)
			return (whithout_expand(lexer_exp));
		else if (check_dollar(lexer_exp) % 2 != 0
			&& check_dollar(lexer_exp) != 1)
		{
			dollar = get_dollar(check_dollar(lexer_exp) - 1, lexer_exp);
			return (dollar);
		}
		else
			return (expanded_word(lexer_exp));
	}
	return (get_char_as_string('$'));
}

void	print_line_expanded(char *line, int fd)
{
	t_lexer	*lexer_exp;
	char	*exp;

	exp = NULL;
	lexer_exp = init_lexer(line);
	while (lexer_exp->c != '\0')
	{
		if (lexer_exp->c == '$')
		{
			exp = expand(lexer_exp);
			if (exp == NULL)
				continue ;
			write(fd, exp, ft_strlen(exp));
			free(exp);
			exp = NULL;
		}
		else
		{
			write(fd, &lexer_exp->c, 1);
			lexer_advance(lexer_exp);
		}
	}
}
