/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 01:36:23 by nel-brig          #+#    #+#             */
/*   Updated: 2022/11/29 01:36:25 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"

char	*join_filename(char **string, char *dollar, char *str)
{
	char	*filename;

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
	return (filename);
}

char	*get_ambiguous_filename(char **string, char *dollar,
			char *str, t_lexer *lexer)
{
	char	*filename;

	filename = NULL;
	filename = join_filename(string, dollar, str);
	str = NULL;
	str = join_after_expand(lexer);
	if (str != NULL)
	{
		filename = ft_strjoin(filename, str);
		free(str);
	}
	return (filename);
}

char	*add_ambiguous_filename(t_data *data, char **string,
			t_lexer *lexer, t_token **token)
{
	char	*filename;
	char	*join;

	filename = NULL;
	join = NULL;
	if (get_type(*token) == AMB)
	{
		data->str = join_with_dollar(data->str);
		filename = get_ambiguous_filename(string, data->dollar,
				data->str, lexer);
		free_all(data->join, data->expand, NULL, NULL);
		return (add_ambiguous(token, filename, data));
	}
	if (*string != NULL)
		join = ft_strdup_free(string);//---
	if (data->join != NULL)
	{
		join = ft_strjoin(join, data->join);
		free(data->join);
	}
	free_all(data->expand, data->str, data->dollar, data);
	return (handle_spaces(join, token));
}

char	*add_ambiguous(t_token **token, char *str, t_data *data)
{
	add_token_back(token, init_token(AMB, str));
	free(data);
	return (NULL);
}

int	is_ambiguous(char *dollar, char *string, char *expand, t_lexer *lexer)
{
	if (dollar == NULL && string == NULL && expand == NULL)
	{
		if (is_space(lexer->c) == 0 || lexer->c == '\0')
			return (1);
	}
	return (-1);
}
