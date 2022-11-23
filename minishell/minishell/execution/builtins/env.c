/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:24:01 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/23 12:46:54 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

int	lines_counter(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	printable(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_env(t_parser *prog, t_env **env)
{
	t_env	*tmp;

	prog = NULL;
	tmp = *env;
	while (tmp)
	{
		if (printable(tmp->line))
		{
			ft_putstr_fd(tmp->line, var->fd_out);
			ft_putstr_fd("\n", var->fd_out);
		}
		tmp = tmp->next;
	}
	if (var->fd_out > 1)
		close(var->fd_out);
}
