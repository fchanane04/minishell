/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:51:43 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/01 18:24:42 by fchanane         ###   ########.fr       */
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

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	leaks_hunter(char ***str)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = *str;
	while (tmp[i])
	{
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(tmp);
	tmp = NULL;
}

char	*var_name(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		i++;
	}
	return (NULL);
}

int	ft_strcmp_export(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && (s1[i] != '=' && s2[i] != '='))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s2[i])
		return (-1);
	return (0);
}

int	main(void)
{
	char	*s1 = ft_strdup("TE=TEST");
	char	*s2 = ft_strdup("=TEST");
	printf("%d\n", ft_strcmp_export(s1, s2));
}