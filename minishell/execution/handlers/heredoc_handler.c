/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:05:49 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/01 15:20:27 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

char	*heredoc_name(int i)
{
	char	*tty;
	char	**split;
	char	*name;
	char	*tmp;

	tmp = ft_strdup(ttyname(0));
	split = ft_split(tmp, 'v');
	tty = ft_strjoin_exec("/tmp", split[1]);
	free(split[0]);
	free(split[1]);
	free(split);
	name = ft_strjoin_exec(tty, ft_itoa(i));
	free(tty);
	//free(tmp);
	return (name);
}

void	write_in_heredoc(t_heredoc *hd, char *filename)
{
	int	status;

	hd->pid = fork();
	signal(SIGINT, SIG_IGN);
	if (!hd->pid)
	{
		while (1)
		{			
			signal(SIGINT, SIG_DFL);
			hd->line = readline("> ");
			if (!hd->line)
				exit(1);
			if (!ft_strcmp(hd->line, filename))
				break ;
			write(hd->fd, hd->line, ft_strlen(hd->line));
			write(hd->fd, "\n", 1);
		}
	}
	waitpid(hd->pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		write (1, "\n", 1);
		var->hd_sig = -303;
	}
	signal(SIGINT, signal_handler);
}

char	*heredoc_save(int fd, char *name)
{
	int		len;
	char	*save;

	len = ft_strlen(name);
	if (fd != -404)
	{
		save = malloc(sizeof(char) * (len + 1));
		return (save);
	}
	return (ft_strdup("NO"));
}

char	**ft_heredoc(t_parser *prog)
{
	t_parser	*tmp;
	t_files		*f;
	t_heredoc	*hd;
	int			i;

	tmp = prog;
	hd = malloc(sizeof(t_heredoc));
	hd->save = malloc(sizeof(char *) * (list_counter(prog) + 1));
	hd->fd = -404;
	var->hd_sig = 0;
	i = 0;
	while (tmp)
	{
		f = tmp->files;
		if (f)
		{
			while (f)
			{
				if (f->type == DEL)
				{
					if (hd->fd != -404)
						unlink(heredoc_name(i));
					hd->fd = open(heredoc_name(i), O_WRONLY | O_TRUNC | O_CREAT, 0777);
					write_in_heredoc(hd, f->filename);
					close(hd->fd);
					if (var->hd_sig == -303)
						return (NULL);
				}
				f = f->next;
			}
			hd->save[i] = heredoc_save(hd->fd, heredoc_name(i));
			hd->fd = -404;
		}	
		tmp = tmp->next;
		i++;
	}
	hd->save[i] = NULL;
	return (hd->save);
}

int	re_init_heredoc(char *heredoc, int fd_in, int err)
{
	if (fd_in == -404)
	{
		var->fd_in = open(heredoc, O_RDONLY, 0644);
		if (var->fd_in == -1)
		{
			error_printer(BASH_ERR, ": ", heredoc);
			perror("");
			var->status = 1;
			return (-1);
		}
	}
	return (err);

}