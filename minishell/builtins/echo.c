/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:20:11 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/14 21:51:10 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	check_opt(char *opt)
{
	int	i;

	i = 0;
	if (!opt)
		return (0);
	if (opt[i] != '-')
		return (0);
	i++;
	if (!opt[i])
		return (0);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_parser *prog)
{
	int	i;
	int	fd;
	int	endl;

	i = 0;
	fd = 1;
	endl = 1;
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
	i = 1;
	while (check_opt(prog->args[i]))
	{
		i++;
		endl = 0;
	}
	while (prog->args[i])
	{
		ft_putstr_fd(prog->args[i], fd);
		if  (prog->args[i + 1])
				ft_putstr_fd(" ", fd);
		i++;
	}
	if (endl)
		ft_putstr_fd("\n", fd);
	if (fd > 1)
		close(fd);
	
}
