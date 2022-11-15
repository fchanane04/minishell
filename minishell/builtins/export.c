/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:24:20 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/15 10:58:36 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	print_with_quotes(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		write(fd, &str[i], 1);
		i++;
	}
	if (str[i] != '\0')
	{
		write(fd, &str[i++], 1);
		write(fd, "\"", 1);
		while (str[i])
		{
			write(fd, &str[i], 1);
			i++;
		}
		write(fd, "\"", 1);
	}
}

void	ft_export(t_parser *prog, t_env **env)
{
	t_env	*tmp;
	int		i;
	int		fd;

	i = 0;
	fd = 1;
	if (prog->out_files)
	{
		while (prog->out_files)
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
	tmp = *env;
	if (!prog->args[1])
	{
		while (tmp)
		{
			ft_putstr_fd("declare -x ", fd);
			print_with_quotes(tmp->line, fd);
			ft_putstr_fd("\n", fd);
			tmp = tmp->next;
		}
	}
	else
	{
		i = 1;
		while (prog->args[i])
		{
			add_env_node(env, new_node(prog->args[i]));
			i++;
		}
	}
	if (fd > 1)
		close(fd);
}