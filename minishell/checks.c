/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:14:04 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/16 00:04:37 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	builtin_check(char *cmd)
{
	int	check;

	check = 0;
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		check = 1;
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		check = 1;
	if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		check = 1;
	if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		check = 1;
	if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		check = 1;
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
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
