/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:21:31 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/03 22:03:17 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

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
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (stock[i])
	{
		j = i + 1;
		while (stock[j])
		{
			if (ft_strcmp_export(stock[i], stock[j]) > 0)
			{
				tmp = stock[i];
				stock[i] = stock[j];
				stock[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_export(stock);
	free(stock);
}

void	add_without_plus(char *arg)
{
	char	**split;
	char	*join;

	split = ft_split_exec(arg, '+');
	join = ft_strjoin_exec(split[0], split[1]);
	leaks_hunter(&split);
	add_env_node(&var->envc, new_node(join));
	free(join);
}

void	add_to_end(char *arg)
{
	t_env	*tmp;
	int		exist;
	char	**split;
	char	*arr;

	tmp = var->envc;
	exist = 0;
	while (tmp)
	{
		arr = arr_create(arg);
		if (!ft_strcmp_export(arr, tmp->line))
		{
			free(arr);
			exist = 1;
			split = ft_split_exec(arg, '=');
			tmp->line = ft_strjoin_exec(tmp->line, split[1]);
			leaks_hunter(&split);
			break ;
		}
		free(arr);
		tmp = tmp->next;
	}
	if (!exist)
		add_without_plus(arg);
}

void	add_or_update(char *arg)
{
	t_env	*tmp;
	int		check;

	tmp = var->envc;
	check = 0;
	while (tmp)
	{
		if (!ft_strcmp_export(arg, tmp->line))
		{
			check = 1;
			tmp->line = ft_strdup(arg);
			break ;
		}
		tmp = tmp->next;
	}
	if (!check)
		add_env_node(&var->envc, new_node(arg));
}
