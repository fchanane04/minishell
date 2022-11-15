/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:24:09 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/15 11:55:36 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

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
