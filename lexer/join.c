/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 01:35:49 by nel-brig          #+#    #+#             */
/*   Updated: 2022/11/29 01:35:51 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"

char	*join_dollar_with_expand(char **dollar, char **expand)
{
	char	*join;

	join = NULL;
	if (expand != NULL)
	{
		join = ft_strjoin(*dollar, *expand);
		*dollar = NULL;
	}
	else if (dollar != NULL)
		join = ft_strdup_free(dollar);
	return (join);
}

char	*join_string_with_quotes(char *s, char c)
{
	char	*a;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (get_quotes(c));
	a = malloc(sizeof(char) * (ft_strlen(s) + 3));
	if (!a)
		return (NULL);
	a[j++] = c;
	while (s[i] != '\0')
		a[j++] = s[i++];
	a[j++] = c;
	a[j] = '\0';
	free(s);
	return (a);
}

char	*join_after_expand(t_lexer *lexer)
{
	char	*str;
	char	*s;
	char	c;

	str = NULL;
	s = NULL;
	while (lexer->c != '\0' && is_whitespaces(lexer->c) != 0
		&& red_or_pipe(lexer->c) != 1)
	{
		if (is_quote(lexer->c) == 0)
		{
			c = lexer->c;
			s = single_quote(lexer, lexer->c);
			s = join_string_with_quotes(s, c);
		}
		else
			s = get_string_without_expand(lexer, &s);
		if (s != NULL)
		{
			str = ft_strjoin(str, s);
			ft_free(&s);
		}
	}
	return (str);
}

char	*join_string_with_char(char *dollar, char c, t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) *(ft_strlen(dollar) + 2));
	if (!str)
		return (NULL);
	while (dollar[i] != '\0')
	{
		str[i] = dollar[i];
		i++;
	}
	str[i++] = c;
	str[i] = '\0';
	free(dollar);
	free(data);
	return (str);
}

char	*join_with_dollar(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc (sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (NULL);
	new[j++] = '$';
	while (str[i] != '\0')
		new[j++] = str[i++];
	new[j] = '\0';
	free(str);
	return (new);
}
