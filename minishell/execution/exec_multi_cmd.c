/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 05:07:43 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/03 17:41:15 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	ft_dup(int fd, int pip, t_parser *next)
{
	if (var->fd_in > 2)
		dup2(var->fd_in, 0);
	else
	{
		if (fd != -1)
			dup2(fd, 0);
	}
	if (var->fd_out > 2)
		dup2(var->fd_out, 1);
	else
	{
		if (next)
			dup2(pip, 1);
	}
}

void	execute_cmd(char **args)
{
	char	*path;
	char	**envv;

	if (var->envc)
	{
		if (isdir(args[0]))
			directory_error(args[0]);
		else
		{
			path = find_path(create_paths(var->envc), args[0]);
			cmd_error_check(args[0], path);
		}
		envv = duplicate(var->envc);
		execve(path, args, envv);
	}
}

int	exec_from_multi(t_parser *prog, int fd, char *heredoc)
{
	int	pid;
	int	err;
	int	pip[2];

	if (file_prep(prog, heredoc) == -1)
		return (-2);
	if (!prog->args)
		return (-2);
	err = pipe(pip);
	if (err == -1)
	{
		printf("%s\n", strerror(errno));
		var->status = 1;
		exit(var->status);
	}
	pid = fork();
	if (!pid)
	{
		ft_dup(fd, pip[1], prog->next);
		close(pip[0]);
		fd = pip[0];
		if (!builtin_check(prog->args[0]))
			execute_cmd(prog->args);
		else
			ft_builtins(prog);
		exit(var->status);
	}
	close(pip[1]);
	if (var->fd_in != 0)
		close(var->fd_in);
	return (0);
}

void	exec_multi_cmd(t_parser *prog, char **heredocs)
{
	t_parser	*tmp;
	int			i;
	int			fd;

	tmp = prog;
	i = 0;
	fd = -1;
	while (tmp)
	{
		fd = exec_from_multi(tmp, fd, heredocs[i]);
		i++;
		tmp = tmp->next;
	}
	close(fd);
}
