/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:47:41 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/23 12:43:08 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	open_infile(t_files *files)
{
	t_files	*tmp;
	int		fd;

	fd = 0;
	tmp = files;
	while (tmp)
	{
		if (tmp->type == IN)
		{
			if (fd != 0)
				close(fd);
			fd = open(tmp->filename, O_RDONLY, 0777);
		}
		tmp = tmp->next;
	}
	return (fd);
}

int	open_outfile(t_files *files)
{
	t_files	*tmp;
	int		fd;

	fd = 1;
	tmp = files;
	while (tmp)
	{
		if (tmp->type == OUT || tmp->type == APP)
		{
			if (fd != 1)
				close(fd);
			if (tmp->type == OUT)
				fd = open(tmp->filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			if (tmp->type == APP)
				fd = open(tmp->filename, O_CREAT | O_WRONLY | O_APPEND, 0777);
		}
		tmp = tmp->next;
	}
	return (fd);
}
