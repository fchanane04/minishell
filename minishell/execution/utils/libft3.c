/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:37:04 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/01 15:20:07 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

static int	ft_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

static int	ft_check_sign(int sign)
{
	if (sign == -1)
		return (0);
	return (-1);
}

long long	ft_atoi(char *str)
{
	int			i;
	int			sign;
	long long	number;

	i = ft_whitespace(str);
	sign = 1;
	number = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		if ((number * 10 + (str[i] - '0')) / 10 != number)
			return (ft_check_sign(sign));
		if (str[i] == '-' || str[i] == '+')
			return (number * sign);
		number = number * 10 + (str[i++] - 48);
	}
	return (number * sign);
}

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