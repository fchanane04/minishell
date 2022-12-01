/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 05:03:37 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/01 17:50:42 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

int	exist_in_env(char *arg, t_env **env)
{
	t_env	*tmp;
	char	**args;
	char	**envline;

	tmp = *env;
	args = ft_split(arg, '=');
	while (tmp)
	{
		envline = ft_split(tmp->line, '=');
		if (!ft_strcmp(args[0], envline[0]))
		{
			leaks_hunter(&envline);
			leaks_hunter(&args);
			return (1);
		}
		tmp = tmp->next;
		leaks_hunter(&envline);
	}
	leaks_hunter(&args);
	return (0);
}

void	update_var(char *arg, t_env **env)
{
	t_env	*tmp;
	char	**args;
	char	**envline;

	tmp = *env;
	args = ft_split(arg, '=');
	while (tmp)
	{
		envline = ft_split(tmp->line, '=');
		if (!ft_strcmp(args[0], envline[0]))
		{
			if (args[1])
			{
				if (!envline[1]
					|| (envline[1] && ft_strcmp(envline[1], args[1])))
					tmp->line = ft_strdup(arg);
			}
			leaks_hunter(&envline);
			break ;
		}
		leaks_hunter(&envline);
		tmp = tmp->next;
	}
	leaks_hunter(&args);
}

char	**export_stock(void)
{
	char	**stock;
	t_env	*current;
	int		i;

	stock = malloc(sizeof(char *) * (env_counter(var->envc) + 1));
	current = var->envc;
	i = 0;
	while (current)
	{
		stock[i] = current->line;
		current = current->next;
		i++;
	}
	stock[i] = NULL;
	return (stock);
}

void	export_printer(char **stock)
{
	int	i;
	int	j;
	char	*tmp;

	i = 0;
	while (stock[i])
	{
		j = i + 1;
		while (stock[j])
		{
			if (ft_strcmp(stock[i], stock[j]) > 0)
			{
				tmp = stock[i];
				stock[i] = stock[j];
				stock[j] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (stock[i])
	{
		printf("%s\n", stock[i]);
		i++;
	}
}

void	ft_export(t_parser *prog)
{
	int	i;

	i = 1;
	if (!prog->args[1])
		export_printer(export_stock());
	// else
	// {
	// 	while (prog->args[i])
	// 	{
	// 		if (!exist_in_env(prog->args[i], &var->envc))
	// 			add_env_node(&var->envc, new_node(prog->args[i]));
	// 		else
	// 			update_var(prog->args[i], &var->envc);
	// 		i++;
	// 	}
	// }
	// if (var->fd_out > 1)
	// 	close(var->fd_out);
	// var->status = 0;
	// t_env	*tmp;
	// int		i;

	// tmp = var->envc;
	// if (!prog->args[1])
	// {
	// 	while (tmp)
	// 	{
	// 		ft_putstr_fd("declare -x ", var->fd_out);
	// 		print_with_quotes(tmp->line, var->fd_out);
	// 		ft_putstr_fd("\n", var->fd_out);
	// 		tmp = tmp->next;
	// 	}
	// }
	// else
	// {
	// 	i = 1;
	// 	while (prog->args[i])
	// 	{
	// 		if (!exist_in_env(prog->args[i], &var->envc))
	// 			add_env_node(&var->envc, new_node(prog->args[i]));
	// 		else
	// 			update_var(prog->args[i], &var->envc);
	// 		i++;
	// 	}
	// }
	// if (var->fd_out > 1)
	// 	close(var->fd_out);
	// var->status = 0;
}
