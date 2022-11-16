/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:13:58 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/10 01:26:08 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_check(t_parser *prog)
{
	t_parser	*tmp;
	char		*line;
	int			fd;
	int			i;

	tmp = prog;
	while (tmp)
	{
		if (tmp->heredoc)
		{
			i = 0;
			while (tmp->heredoc[i])
			{
				fd = open(".tmp", O_RDWR | O_APPEND | O_CREAT);
				line = readline("> ");
				while (ft_strncmp(tmp->heredoc[i], line, ft_strlen(line) - 1))
				{
					write(fd, line, ft_strlen(line));
					line = readline("> ");
				}
				// ft_putstr_fd("you have closed ", 1);
				// ft_putstr_fd(tmp->heredoc[i], 1);
				// ft_putstr_fd("\n", 1);
				close(fd);
				unlink(".tmp");
				i++;
			}
		}
		tmp = tmp->next;
	}
}
