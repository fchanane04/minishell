/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:46:18 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/15 10:08:45 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include"minishell.h"

t_env	*new_node(char *line)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->first = line[0];
	node->line = ft_strdup(line);
	node->next = NULL;
	return (node);
}

void	add_env_node(t_env **env, t_env *node)
{
	t_env	*tmp;

	tmp = *env;
	if (!*env)
		*env = node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

t_env	*clone_env(char **env)
{
	t_env	*clone;
	int		i;

	clone = NULL;
	i = 0;
	while (env[i])
	{
		add_env_node(&clone, new_node(env[i]));
		i++;
	}
	return (clone);
}

char *get_envc(t_env *env, char *var)
{
	t_env	*tmp;
	int		start;
	int		len;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(var , tmp->line, ft_strlen(var)))
		{
			start = ft_strlen(var) + 1;
			len = ft_strlen(tmp->line) - start;
			return (ft_substr(tmp->line, start, len));
		}
		tmp = tmp->next;
	}
	return (NULL);
}
