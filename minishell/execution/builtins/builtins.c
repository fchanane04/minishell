/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:45:57 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/03 21:36:33 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	exec_builtin(t_parser *prog, char *heredoc)
{
	if (file_prep(prog, heredoc) == -1)
		return ;
	ft_builtins(prog);
}

void	ft_builtins(t_parser *prog)
{
	if (!ft_strcmp(prog->args[0], "echo"))
		ft_echo(prog);
	if (!ft_strcmp(prog->args[0], "cd"))
		ft_cd(prog);
	if (!ft_strcmp(prog->args[0], "pwd"))
		ft_pwd(prog);
	if (!ft_strcmp(prog->args[0], "env"))
		ft_env(prog);
	if (!ft_strcmp(prog->args[0], "unset"))
		ft_unset(prog);
	if (!ft_strcmp(prog->args[0], "export"))
		ft_export(prog);
	if (!ft_strcmp(prog->args[0], "exit"))
		ft_exit(prog);
}
