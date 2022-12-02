/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 05:03:37 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/02 15:51:43 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	print_export(char **stock)
{
	int	i;

	i = 0;
	while (stock[i])
	{
		ft_putstr_fd("declare -x ", var->fd_out);
		print_with_quotes(stock[i], var->fd_out);
		ft_putstr_fd("\n", var->fd_out);
		i++;
	}
}

int	last_check(char *arg)
{
	t_env	*tmp;

	tmp = var->envc;
	while (tmp)
	{
		if (!ft_strcmp_export(arg, tmp->line))
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	export_var(char *arg)
{
	int		i;
	int		check;
	t_env	*tmp;

	check = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			check = 1;
			if (arg[i - 1] == '+')
				add_to_end(arg);
			else
				add_or_update(arg);
		}
		i++;
	}
	tmp = var->envc;
	if (!check)
		check = last_check(arg);
	if (!check)
		add_env_node(&var->envc, new_node(arg));
}

int	valid_name_exp(char *str)
{
	int		i;
	char	*name;

	name = var_name(str);
	if (name[ft_strlen(name) - 1] == '+')
		name[ft_strlen(name) - 1] = '\0';
	i = 0;
	if (name[i] != '_' && !ft_isalpha(name[i]))
	{
		free(name);
		return (0);
	}
	i++;
	while (name[i])
	{
		if (name[i] != '_' && !ft_isalnum(name[i]))
		{
			free(name);
			return (0);
		}
		i++;
	}
	free(name);
	return (1);
}

void	ft_export(t_parser *prog)
{
	int		i;

	i = 1;
	fflush(stdout);
	if (!prog->args[1])
		export_printer(export_stock());
	else
	{
		while (prog->args[i])
		{
			if (!valid_name_exp(prog->args[i]))
				identifier_error(prog->args[i], "export");
			else
				export_var(prog->args[i]);
			i++;
		}
	}
	if (var->fd_out > 1)
		close(var->fd_out);
}
