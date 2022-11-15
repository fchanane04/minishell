/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:24:01 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/15 11:03:18 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	lines_counter(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	printable(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_env(t_parser *prog, t_env **env)
{
	int		i;
	int		fd;
	t_env	*tmp;

	i = 0;
	fd = 1;
	if (prog->out_files)
	{
		while (prog->out_files[i])
		{
			fd = open(prog->out_files[i], O_RDWR | O_CREAT | O_TRUNC, 0777);
			if (fd < 0)
				exit(1);
			if (!prog->out_files[i + 1])
				break ;
			else
				close(fd);
			i++;
		}
	}
	i = 0;
	if (prog->append)
	{
		while (prog->append[i])
		{
			fd = open(prog->append[i], O_RDWR | O_CREAT | O_APPEND, 0777);
			if (fd < 0)
				exit(1);
			if (!prog->append[i + 1])
				break ;
			else
				close(fd);
			i++;
		}
	}
	tmp = *env;
	while (tmp)
	{
		if (printable(tmp->line))
		{
			ft_putstr_fd(tmp->line, fd);
			ft_putstr_fd("\n", fd);
		}
		tmp = tmp->next;
	}
	if (fd > 1)
		close(fd);
}
