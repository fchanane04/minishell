/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 05:07:00 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/04 01:33:22 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	cmd_error_check(char *arg, char *path)
{
	if (!path)
	{
		if (access(arg, F_OK) && last_with_back(arg))
			no_directory(arg);
		if (arg[0] == '.' || arg[0] == '/')
		{
			if (access(arg, X_OK))
				permission_error(arg);
		}
		else
			not_found_error(arg);
	}
}

void	single_cmd_wait(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		var->status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		var->status = WTERMSIG(status) + 128;
}

void	ft_dup_in_single(void)
{
	dup2(var->fd_in, 0);
	dup2(var->fd_out, 1);
}

void	exec_single_cmd(t_parser *prog, char *heredoc)
{
	int		pid;
	char	*path;

	if (file_prep(prog, heredoc) == -1 || !prog->args)
		return ;
	signal_before();
	pid = fork();
	if (!pid)
	{
		signal_in();
		ft_dup_in_single();
		if (var->envc)
		{
			if (access(prog->args[0], X_OK))
			{
				if (isdir(prog->args[0]))
					directory_error(prog->args[0]);
				else
				{
					path = find_path(create_paths(var->envc), prog->args[0]);
					cmd_error_check(prog->args[0], path);
				}
			}
			else
				path = ft_strdup(prog->args[0]);
			execve(path, prog->args, duplicate(var->envc));
		}
	}
	single_cmd_wait(pid);
	cleanup_fd();
}
