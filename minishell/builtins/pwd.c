/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:23:49 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/14 21:53:03 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	ft_pwd(t_parser *prog)
{
	char	buff[100];
	int		fd;
	int		i;

	i = 0;
	fd = 1;
	getcwd(buff, sizeof(buff));
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
	write(fd, buff, ft_strlen(buff));
	write(fd, "\n", 1);
	if (fd > 1)
		close(fd);
}