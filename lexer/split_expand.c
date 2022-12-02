/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:32:03 by nel-brig          #+#    #+#             */
/*   Updated: 2022/11/25 16:32:05 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"

int	check_space(char *expand)
{
	int	i;

	i = 0;
	if (expand == NULL)
		return (1);
	while (expand[i] != '\0')
	{
		if (is_whitespaces(expand[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	count_word(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

int	get_type(t_token *token)
{
	if (is_redirection(token) == 1)
		return (AMB);
	return (WORD);
}

char	*convert_tabs_into_spaces(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) *(ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '\t')
			str[i] = ' ';
		new[i] = str[i];
		i++;
	}
	free(str);
	new[i] = '\0';
	return (new);
}

char	*handle_spaces(char *expand, t_token **token)
{
	char	**a;
	int		count;
	int		i;
	int		type;

	i = 0;
	expand = convert_tabs_into_spaces(expand);
	a = ft_split(expand, ' ');
	count = count_word(a);
	type = get_type(*token);
	while (i < count)
	{
		add_token_back(token, init_token(type, a[i]));
		i++;
	}
	free(a);
	return (NULL);
}
