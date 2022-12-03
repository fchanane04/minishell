/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:23:14 by nel-brig          #+#    #+#             */
/*   Updated: 2022/12/03 19:23:15 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "minishell.h"

void	init_global_var(char **envp)
{
	var = malloc(sizeof(t_global));
	var->envc = clone_env(envp);
	var->status = 0;
	var->fd_out = 1;
	var->fd_in = 0;
}

void	init_variables(t_token **token, t_parser **cmd_table,
		char **envp, char **line)
{
	*token = NULL;
	*cmd_table = NULL;
	*line = NULL;
	init_global_var(envp);
	signal(SIGINT, signal_handler);
}
