/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:42:38 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/23 12:43:47 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

int	check_limits(char *arg)
{
	long long	number;

	number = ft_atoi(arg);
	if ((arg[0] == '-') && (number >= 0))
		return (0);
	if ((arg[0] != '-') && (number <= 0))
		return (0);
	return (1);
}

int	is_valid_num(char *arg)
{
	int			i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (check_limits(arg));
}

void	exit_error(char *arg, char *error)
{
	ft_putstr_fd("bash: exit: ", 1);
	if (arg)
		ft_putstr_fd(arg, 1);
	ft_putstr_fd(error, 1);
}

void	ft_exit(t_parser *prog)
{
	int	err;

	ft_putstr_fd("exit\n", 1);
	if (!prog->args[1])
		err = 1;
	if (prog->args[1] && !prog->args[2])
	{
		if (is_valid_num(prog->args[1]))
		{
			var->status = (unsigned char)ft_atoi(prog->args[1]);
			err = 1;
		}
		else
		{
			exit_error(prog->args[1], EXIT_ERR1);
			var->status = 255;
			err = 1;
		}		
	}
	if (prog->args[1] && prog->args[2])
	{
		exit_error(NULL, EXIT_ERR2);
		var->status = 1;
		err = 0;
	}
	if (err)
		exit(var->status);
}
