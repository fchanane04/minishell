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

char	*join_string_with_char(char *dollar, char c)
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
	return (str);
}

char	*ft_strdup_free(char **s)
{
	char	*a;
	int		i;

	i = 0;
	a = malloc(sizeof(char) * (ft_strlen(*s) + 1));
	if (!a)
		return (NULL);
	while (s[0][i] != '\0')
	{
		a[i] = s[0][i];
		i++;
	}
	ft_free(s);
	return (a);
}
