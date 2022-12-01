/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:31:42 by nel-brig          #+#    #+#             */
/*   Updated: 2022/11/25 16:31:46 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"

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
	return (count);
}

char	*get_dollar(int size, t_lexer *lexer)
{
	char	*s;
	int		i;

	i = 0;
	if (size == 0)
		return (NULL);
	s = malloc(sizeof(char) * (size + 1));
	if (!s)
		exit(EXIT_FAILURE);
	while (i < size)
	{
		s[i++] = lexer->c;
		lexer_advance(lexer);
	}
	s[i] = '\0';
	return (s);
}

char	*whithout_expand(t_lexer *lexer)
{
	char	*s;
	char	*str;

	s = NULL;
	str = NULL;
	str = get_dollar(check_dollar(lexer), lexer);
	skip(lexer, '$');
	while (ft_isalnum(lexer->c) || lexer->c == '_')
	{
		s = get_char_as_string(lexer->c);
		str = ft_strjoin(str, s);
		free(s);
		s = NULL;
		lexer_advance(lexer);
	}
	return (str);
}

char	*get_join(t_data *data)
{
	char	*join;

	join = NULL;
	if (data->expand == NULL && data->dollar != NULL)
		join = strdup(data->dollar);
	else
		join = creat_new_string(data->dollar, data->expand);
	return (join);
}

char	*expand_dollar(t_lexer *lexer, t_token **token, char **string, int flag)
{
	t_data	*data;
	char	*join;

	join = NULL;
	data = allocate();
	data->dollar = get_dollar(check_dollar(lexer) - 1, lexer);
	if (ft_is_digit(lexer->line[lexer->i + 1]))
	{
		skip_first_digit(lexer);
		join = ft_strdup_and_free(data->dollar);
		free(data);
		return (join);
	}
	lexer_advance(lexer);
	if (special_characters(lexer->c) == 1)
		return (join_string_with_char(data->dollar, '$', data));
	data->str = get_string_to_expand(lexer);
	if (data->str == NULL)
		return (join_string_with_char(data->dollar, '$', data));
	data->expand = get_env(data->str);
	if (is_ambiguous(data->dollar, *string, data->expand, lexer) == 1)
		return (add_ambiguous(token, join_with_dollar(data->str), data));
	if (data->expand != NULL || data->dollar != NULL)
		data->join = get_join(data);
	if (check_space(data->join) == 0 && flag != 1)
		return (add_ambiguous_filename(data, string, lexer, token));
	if (data->join != NULL)
		join = ft_strdup_and_free(data->join);
	free_all(data->str, data->dollar, data->expand, data);
	return (join);
}
