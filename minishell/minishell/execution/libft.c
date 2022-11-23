/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:08:02 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/23 12:48:44 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char)s1[i]) != ((unsigned char)s2[i]))
			return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
		if (!s1[i] || !s2[i])
			break ;
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

char	*ft_strdup(char *s1)
{
	char			*ptr;
	unsigned int	i;

	ptr = malloc (ft_strlen(s1) + 1);
	i = 0;
	if (ptr)
	{
		while (s1[i])
		{
			ptr[i] = (char)s1[i];
			i++;
		}
	ptr[i] = '\0';
	}
	return (ptr);
}

char	*ft_substr(char *s, int start, int len)
{
	int	i;
	char			*sub;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	sub = malloc (sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (s[start + i] && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static int      ft_whitespace(char *str)
{
        int     i;

        i = 0;
        while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
                || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
                i++;
        return (i);
}

static int      ft_check_sign(int sign)
{
        if (sign == -1)
                return (0);
        return (-1);
}

long long	ft_atoi(char *str)
{
        int                     i;
        int                     sign;
        long long       number;

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

// static int	ft_count(char *s, char c)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i])
// 	{
// 		while (s[i] == c && s[i] != 0)
// 			i++;
// 		if (s[i] != '\0')
// 			count++;
// 		while (s[i] != c && s[i] != 0)
// 			i++;
// 	}
// 	return (count);
// }

// static void	fill_in(char *s, char c, char **split)
// {
// 	int	i;
// 	int	start;
// 	int	end;

// 	i = 0;
// 	start = 0;
// 	end = 0;
// 	while (i < ft_count(s, c))
// 	{
// 		while (s[start] == c)
// 			start++;
// 		end = start;
// 		while (s[start] != c && s[start] != '\0')
// 			start++;
// 		split[i] = ft_substr(s, end, (start - end));
// 		if (!split[i])
// 		{
// 			free(split[i]);
// 			break ;
// 		}
// 		i++;
// 	}
// 	split[i] = NULL;
// }

// char	**ft_split(char	*s, char c)
// {
// 	char	**split;

// 	split = malloc (sizeof(char *) * (ft_count(s, c) + 1));
// 	if (!split)
// 		return (NULL);
// 	fill_in(s, c, split);
// 	return (split);
// }

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// int	ft_isalnum(int c)
// {
// 	if (ft_isdigit(c) || ft_isalpha(c))
// 		return (1);
// 	return (0);
// }

char	*ft_strjoin_mod(char *s1, char *s2)
{
	char			*join;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	join = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!join)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	join[i++] = '/';
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}
