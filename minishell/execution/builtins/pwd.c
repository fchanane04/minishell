/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 04:18:38 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/03 21:51:30 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	ft_pwd(t_parser *prog)
{
	char	*buff;

	prog = NULL;
	buff = getcwd(0, 0);
	if (!buff)
		buff = ft_strdup(get_envc(var->envc, "PWD"));
	write(var->fd_out, buff, ft_strlen(buff));
	write(var->fd_out, "\n", 1);
	free(buff);
	if (var->fd_out > 1)
		close(var->fd_out);
	var->status = 0;
}
