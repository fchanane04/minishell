/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:14:04 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/23 12:43:24 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	builtin_check(char *cmd)
{
	int	check;

	check = 0;
	if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
		check = 1;
	if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
		check = 1;
	if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		check = 1;
	if (!ft_strncmp(cmd, "env", ft_strlen("env")))
		check = 1;
	if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
		check = 1;
	if (!ft_strncmp(cmd, "export", ft_strlen("export")))
		check = 1;
	if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
		check = 1;
	return (check);
}

int	fork_check(t_parser *prog)
{
	t_parser	*tmp;
	int			check;

	check = 0;
	tmp = prog;
	while (tmp)
	{
		check++;
		tmp = tmp->next;
	}
	if (check == 1)
	{
		if (!prog->args)
			check = 1;
		else
			if (builtin_check(prog->args[0]))
				check = 0;
	}
	return (check);
}
