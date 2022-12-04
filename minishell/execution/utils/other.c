/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:51:05 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/03 12:08:40 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	error_printer(char *bef, char *aft, char *filename)
{
	ft_putstr_fd(bef, 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(aft, 2);
}

void	cleanup_fd(void)
{
	if (var->fd_out > 2)
	{
		close(var->fd_out);
		var->fd_out = 1;
	}
	if (var->fd_in > 2)
	{
		close(var->fd_in);
		var->fd_in = 0;
	}
}

void	print_with_quotes(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		write(fd, &str[i], 1);
		i++;
	}
	if (str[i] != '\0')
	{
		write(fd, &str[i++], 1);
		write(fd, "\"", 1);
		while (str[i])
		{
			write(fd, &str[i], 1);
			i++;
		}
		write(fd, "\"", 1);
	}
}

int	isdir(char *fileName)
{
	struct stat	path;

	stat(fileName, &path);
	return (S_ISDIR(path.st_mode));
}

int	is_file(char *arg)
{
	char	**split;
	int		fd;

	split = ft_split_exec(arg, '/');
	fd = open(split[0], O_RDONLY, 0644);
	if (fd > 0)
	{
		leaks_hunter(&split);
		close(fd);
		return (1);
	}
	return (0);
}
