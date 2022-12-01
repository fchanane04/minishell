/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 01:36:42 by nel-brig          #+#    #+#             */
/*   Updated: 2022/11/29 01:36:44 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"

char	*skip_first_digit(t_lexer *lexer)
{
	lexer_advance(lexer);
	lexer_advance(lexer);
	return (NULL);
}

void	ft_free(char **s)
{
	if (*s != NULL)
	{
		free(*s);
		*s = NULL;
	}
}

void	expand_or_string(t_lexer *lexer, t_token **token, char **str, char **s)
{
	if (lexer->c == '$' && (is_quote(lexer->line[lexer->i + 1]) == 0))
		lexer_advance(lexer);
	else if (lexer->c == '$')
		*s = dollar(lexer, token, str, 0);
	else
		*s = get_str(lexer);
}

char	*join_and_free(char *str, char **s)
{
	str = ft_strjoin(str, *s);
	ft_free(s);
	return (str);
}

int	is_redirection(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (token == NULL)
		return (0);
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->type != WORD)
		return (1);
	return (0);
}
