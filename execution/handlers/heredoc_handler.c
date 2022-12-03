/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:05:49 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/02 18:06:16 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

char	*create_heredoc_name(int i)
{
	char	*tty;
	char	*name;
	char	**split;
	char	*heredoc;

	tty = ttyname(0);
	split = ft_split_exec(tty, 'v');
	name = ft_strjoin_exec("/tmp", split[1]);
	heredoc = ft_strjoin_exec(name, ft_itoa(i));
	leaks_hunter(&split);
	free(name);
	return (heredoc);
}

int	check_other_heredoc(t_files *file)
{
	t_files	*tmp;

	tmp = file;
	while (tmp)
	{
		if (tmp->type == DEL)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}


int	open_and_write(char *filename, char *name)
{
	int	fd;
	int	pid;
	int	status;
	char	*line;

	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (!pid)
	{
		while (1)
		{
			signal(SIGINT, SIG_DFL);
			line = readline("> ");
			if (!line)
				exit(1);
			if (!ft_strcmp(line, filename))
				exit(1);
			print_line_expanded(line, fd);//expand here
			write(fd, "\n", 1);
		}
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		//write (1, "\n", 1);
		var->flag = -303;
	}
	signal(SIGINT, signal_handler);
	return (fd);
}

char	*save_in(char *name)
{
	if (!name)
		return (ft_strdup("NO"));
	else
		return (ft_strdup(name));
}

char	**ft_heredoc(t_parser *prog)
{
	t_parser	*tmp;
	t_files		*file;
	char		*name;
	char		**save;
	int			i;
	int			fd;
	int			check;

	tmp = prog;
	i = 0;
	check = 0;
	save = malloc(sizeof(char *) * (list_counter(prog) + 1));
	name = NULL;
	while (tmp)
	{
		file = tmp->files;
		while (file)
		{
			if (file->type == DEL)
			{
				check = 1;
				name = create_heredoc_name(i);
				fd = open_and_write(file->filename, name);
				if (var->flag == -303)
					return (NULL);
				close(fd);
				if (check_other_heredoc(file->next))
				{
					unlink(name);
					free(name);
				}
			}
			file = file->next;
		}
		if (check)
			save[i] = save_in(name);
		else
			save[i] = ft_strdup("NO");
		tmp = tmp->next;
		check = 0;
		i++;
	}
	save[i] = NULL;
	return (save);
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