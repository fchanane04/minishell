/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 07:07:35 by nel-brig          #+#    #+#             */
/*   Updated: 2022/12/01 07:07:36 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"

void	skip(t_lexer *lexer, char c)
{
	while (lexer->c == c)
		lexer_advance(lexer);
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

char	*get_quotes(char c)
{
	char	*s;

	s = malloc(sizeof(char) * 3);
	if (!s)
		return (NULL);
	s[0] = c;
	s[1] = c;
	s[2] = '\0';
	return (s);
}

t_data	*allocate(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->dollar = NULL;
	data->expand = NULL;
	data->str = NULL;
	data->join = NULL;
	return (data);
}

void	free_all(char *s, char *str, char *string, t_data *data)
{
	if (s != NULL)
		free(s);
	if (str != NULL)
		free(str);
	if (string != NULL)
		free(string);
	if (data != NULL)
		free(data);
}
