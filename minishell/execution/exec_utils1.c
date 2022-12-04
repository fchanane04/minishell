/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 12:19:27 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/04 01:27:00 by fchanane         ###   ########.fr       */
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
	no_name = ft_split_exec(tmp->line, '=');
	paths = ft_split_exec(no_name[1], ':');
	free(no_name[0]);
	free(no_name[1]);
	free(no_name);
	return (paths);
}

char	*find_path(char **paths, char *cmd)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	while (paths[i])
	{
		path = ft_strjoin_mod(paths[i], cmd);
		if (!access(path, X_OK))
		{
			free_paths(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_paths(paths);
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
