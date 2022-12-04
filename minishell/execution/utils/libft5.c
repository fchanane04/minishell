/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 12:06:10 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/03 12:07:01 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

static int	ft_count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i] != 0)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != 0)
			i++;
	}
	return (count);
}

static void	fill_in(char *s, char c, char **split)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	while (i < ft_count(s, c))
	{
		while (s[start] == c)
			start++;
		end = start;
		while (s[start] != c && s[start] != '\0')
			start++;
		split[i] = ft_substr(s, end, (start - end));
		if (!split[i])
		{
			free(split[i]);
			break ;
		}
		i++;
	}
	split[i] = NULL;
}

char	**ft_split_exec(char *s, char c)
{
	char	**split;

	split = malloc (sizeof(char *) * (ft_count(s, c) + 1));
	if (!split)
		return (NULL);
	fill_in(s, c, split);
	return (split);
}
