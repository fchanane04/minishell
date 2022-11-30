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

void	skip(t_lexer *lexer, char c)
{
	while (lexer->c == c)
		lexer_advance(lexer);
}

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

char	*creat_new_string(char *s1, char *s2)
{
	char	*a;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 != NULL)
		return (strdup(s2));
	else if (s1 == NULL)
		return (NULL);
	a = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!a)
		return (NULL);
	while (s1[i] != '\0')
		a[j++] = s1[i++];
	i = 0;
	while (s2[i])
		a[j++] = s2[i++];
	a[j] = '\0';
	return (a);
}

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

char *get_quotes(char c)
{
	char	*s;

	s = malloc(sizeof(char) * 3);
	if (!s)
		return(NULL);
	s[0] = c;
	s[1] = c;
	s[2] = '\0';
	return(s);
}

char *join_string_with_quotes(char *s, char c)
{
	char	*a;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s == NULL)
		return(get_quotes(c));
	a = malloc(sizeof(char) * (ft_strlen(s) + 3));
	if (!a)
		return (NULL);
	a[j++] = c;
	while (s[i] != '\0')
		a[j++] = s[i++];
	a[j++] = c;
	a[j] = '\0';
	free(s);
	s = NULL;
	return (a);
}

char *join_filename(char **string, char *dollar, char *str)
{
	char *filename;

	filename = NULL;
	if (*string != NULL)
		filename = ft_strdup_free(string);
	if (dollar != NULL)
	{
		filename = ft_strjoin(filename, dollar);
		free(dollar);
	}
	if (str != NULL)
	{
		filename = ft_strjoin(filename, str);
		free(str);
	}
	return(filename);
}

char *join_after_expand(t_lexer *lexer)
{
	char	*str;
	char	*s;
	char	c;

	str = NULL;
	s = NULL;
	while (lexer->c != '\0' && is_whitespaces(lexer->c) != 0 && red_or_pipe(lexer->c) != 1)
	{
		if(is_quote(lexer->c) == 0)
		{
			c = lexer->c;
			s = single_quote(lexer, lexer->c);
			s = join_string_with_quotes(s, c);
		}
		else
			s = get_str(lexer);
		if (s != NULL)
		{
			str = ft_strjoin(str, s);
			ft_free(&s);
		}
	}
	return (str);
}

char *get_ambiguous_filename(char **string, char *dollar, char *str, t_lexer *lexer)
{
	char	*filename;

	filename = NULL;
	filename = join_filename(string, dollar, str);//>{---$a}===
	str = NULL;
	str = join_after_expand(lexer);//>---$a{===}
	if (str != NULL)
	{
		filename = ft_strjoin(filename, str);
		free(str);
	}
	return (filename);
}

char	*expand_dollar(t_lexer *lexer, t_token **token, char **string, int flag)
{
	char	*str;
	char	*expand;
	char	*dollar;
	char	*join;
	char	*amb_filename;

	dollar = NULL;
	str = NULL;
	expand = NULL;
	join = NULL;
	amb_filename = NULL;
	dollar = get_dollar(check_dollar(lexer) - 1, lexer);
	lexer_advance(lexer);
	if (special_characters(lexer->c) == 1)
		return (join_string_with_char(dollar, '$'));
	str = get_string_to_expand(lexer);
	if (str == NULL)
		return (join_string_with_char(dollar, '$'));//with free dollar and assign it to null
	expand = get_env(str);
	if (is_ambiguous(dollar, *string, expand, lexer) == 1)
		return (add_ambiguous(token, str));
	if (expand == NULL && dollar != NULL)
		join = strdup(dollar);
	else
		join = creat_new_string(dollar, expand);
	if (check_space(join) == 0 && flag != 1)
	{
		if (get_type(*token) == AMB)
		{
			amb_filename = get_ambiguous_filename(string, dollar, str, lexer);//with free str, dollar, string
			ft_free(&join);
			ft_free(&expand);
			return(add_ambiguous(token, amb_filename));
		}
		ft_free(&expand);
		ft_free(&str);
		return (handle_spaces(join, token));
	}
	ft_free(&str);
	ft_free(&dollar);
	ft_free(&expand);
	return (join);
 }
