/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:25:57 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/23 12:43:30 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	exec_builtin(t_parser *prog, t_env **env)
{
	if (!ft_strncmp(prog->args[0], "echo", ft_strlen(prog->args[0])))
		ft_echo(prog);
	if (!ft_strncmp(prog->args[0], "cd", ft_strlen(prog->args[0])))
		ft_cd(prog, env);
	if (!ft_strncmp(prog->args[0], "pwd", ft_strlen(prog->args[0])))
		ft_pwd(prog);
	if (!ft_strncmp(prog->args[0], "env", ft_strlen(prog->args[0])))
		ft_env(prog, env);
	if (!ft_strncmp(prog->args[0], "unset", ft_strlen(prog->args[0])))
		ft_unset(prog, env);
	if (!ft_strncmp(prog->args[0], "export", ft_strlen(prog->args[0])))
		ft_export(prog, env);
	if (!ft_strncmp(prog->args[0], "exit", ft_strlen(prog->args[0])))
		ft_exit(prog);
}