/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:42:34 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/04 01:46:36 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	set_used_vars(void)
{
	var->fd_in = 0;
	var->fd_out = 1;
	var->status = 0;
}

void	clean_after_heredoc(char **save)
{
	int	i;

	i = 0;
	while (save[i])
	{
		if (ft_strcmp("NO", save[i]))
			unlink(save[i]);
		free(save[i]);
		i++;
	}
	free(save);
}

void	ft_execute(t_parser *prog)
{
	int		typ;
	char	**save;

	if (!prog)
		return ;
	typ = exec_type_check(prog);
	save = ft_heredoc(prog);
	if (!save)
		return ;
	if (var->flag == -303)
		return ;
	set_used_vars();
	if (typ == 0)
		exec_builtin(prog, save[0]);
	if (typ == 1)
		exec_single_cmd(prog, save[0]);
	if (typ == 2)
		exec_multi_cmd(prog, save);
	clean_after_heredoc(save);
}
