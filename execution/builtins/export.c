/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:24:20 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/23 12:43:51 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (*(s1 + i) != '\0')
	{
		if (*(s1 + i) < *(s2 + i))
			return (-1);
		if (*(s1 + i) > *(s2 + i))
			return (1);
		i++;
	}
	if (*(s2 + i) != '\0')
		return (-1);
	return (0);
}

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
				if (!envline[1] || (envline[1] && ft_strcmp(envline[1], args[1])))
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



void	ft_export(t_parser *prog, t_env **env)
{
	t_env	*tmp;
	//t_env	*exp_env;
	int		i;

	tmp = *env;
	if (!prog->args[1])
	{
		//exp_env = sorted_env(env);
		//tmp = exp_env;
		while (tmp)
		{
			ft_putstr_fd("declare -x ", var->fd_out);
			print_with_quotes(tmp->line, var->fd_out);
			ft_putstr_fd("\n", var->fd_out);
			tmp = tmp->next;
		}
		//cleanup_exp(&exp_env);
	}
	else
	{
		i = 1;
		while (prog->args[i])
		{
			if (!exist_in_env(prog->args[i], env))
				add_env_node(env, new_node(prog->args[i]));
			else
				update_var(prog->args[i], env);
			i++;
		}
	}
	if (var->fd_out > 1)
		close(var->fd_out);
}