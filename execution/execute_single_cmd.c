/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:46:53 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/23 13:17:07 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	**create_paths(t_env *env)
{
	int		i;
	t_env	*tmp;
	char	**paths;
	char	**no_name;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->line, "PATH", 4))
			break ;
		tmp = tmp->next;
	}
	no_name = ft_split(tmp->line, '=');
	paths = ft_split(no_name[1], ':');
	free(no_name[0]);
	free(no_name[1]);
	free(no_name);
	return (paths);
}

char	*find_path(char **PATHS, char *cmd)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	if (!access(cmd, X_OK))
	{
		free_paths(PATHS);
		return (cmd);
	}
	while (PATHS[i])
	{
		path = ft_strjoin_mod(PATHS[i], cmd);
		if (!access(path, X_OK))
		{
			free_paths(PATHS);
			return (path);
		}
		free(path);
		i++;
	}
	free_paths(PATHS);
	return (NULL);
}

char	**duplicate(t_env *env)
{
	char	**envv;
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envv = malloc(sizeof(char *) * (i + 1));
	tmp = env;
	i = 0;
	while (tmp)
	{
		envv[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	envv[i] = NULL;
	return (envv);
	
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}
#include <errno.h>
 #include <sys/stat.h>
void	is_a_directory(char *bin_path)
{
	struct stat	data;

	if (stat(bin_path, &data) == -1)
	{
		strerror(errno);
		write(2, "Bash : Command not found\n", sizeof("Bash : Command not found\n"));
		var->status = 127;
		printf("erno == %d, var->status == %d\n", errno, var->status);
		// exit(errno);
	}
	if (S_ISDIR(data.st_mode) == 1)
	{
		strerror(errno);
		write(2, "bash : is a directory\n", sizeof("bash : is a directory\n"));
		exit(errno);
	}
}

void	execute_single_cmd(t_parser *prog)
{
	char	*path;
	int		pid;
	char	**envv;

	// if (prog->files)
	// {
	// 	var->fd_in = open_infile(prog->files);
	// 	var->fd_out = open_outfile(prog->files);
	// }
	pid = fork();
	if (pid == 0)
	{
		dup2(var->fd_in, 0);
		dup2(var->fd_out, 1);
		path = find_path(create_paths(var->envc), prog->args[0]);
		is_a_directory(path);
		
		/*
		if (!path)
		{
			//var->status = 127;
			write(2, "bash :command not found: ", 25);
			ft_putstr_fd(prog->args[0], 2);
			write(2, "\n", 2);
			exit(*exit_status_setter(127));
		}
		*/
		envv = duplicate(var->envc);
		if (execve(path, prog->args, envv) <= -1)
		{
			perror("execve");
			exit(1);
		}
	}
	wait(NULL);
}