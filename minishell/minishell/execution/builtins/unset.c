/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:24:09 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/23 12:45:39 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

int	valid_name(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '_' && (str[i] < 'A' || str[i] > 'z' || (str[i] < 'Z' && str[i] > 'a')))
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	unset_error(char *str)
{
	ft_putstr_fd("bash: unset: `", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\': not a valid identifier\n", 1);
}

void	ft_unset(t_parser *prog, t_env **env)
{
	int		i;
	t_env	*tmp;
	t_env	*freeit;

	i = 1;
	if (!prog->args[i])
		return ;
	while (prog->args[i])
	{
		if (prog->args[i][0] == '#')
			return ;
		if (!valid_name(prog->args[i]))
			unset_error(prog->args[i]);
		tmp = *env;
		while (*env && !ft_strncmp(tmp->line, prog->args[i], ft_strlen(prog->args[i])))
		{
			*env = tmp->next;
			tmp = *env;
		}
		i++;
	}
	if (tmp)
	{
		while (prog->args[i])
		{
			tmp = *env;
			freeit = tmp->next;
			while (freeit)
			{
				if (!ft_strncmp(freeit->line, prog->args[i], ft_strlen(prog->args[i])))
				{
					tmp->next = freeit->next;
					freeit->next = NULL;
					free(freeit);
					freeit = tmp->next;
				}
				else
				{
					tmp = freeit;
					freeit = freeit->next;
				}
			}
			i++;
		}
	}
}
