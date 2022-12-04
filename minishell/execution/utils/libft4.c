/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:51:43 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/03 12:08:16 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*var_name(char *line)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (!line[i])
		name = ft_strdup(line);
	else
	{
		name = malloc(sizeof(char) * (i + 1));
		j = 0;
		while (j < i)
		{
			name[j] = line[j];
			j++;
		}
		name[j] = '\0';
	}
	return (name);
}

int	ft_strcmp_export(char *s1, char *s2)
{
	char	*str1;
	char	*str2;
	int		i;

	str1 = var_name(s1);
	str2 = var_name(s2);
	i = ft_strcmp(str1, str2);
	free(str1);
	free(str2);
	return (i);
}

int	last_with_back(char *arg)
{
	int	i;

	i = ft_strlen(arg);
	if (arg[i - 1] == '/')
		return (1);
	return (0);
}

int	list_counter(t_parser *prog)
{
	t_parser	*tmp;
	int			count;

	tmp = prog;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
