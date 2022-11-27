/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:23:49 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/23 12:46:32 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	ft_pwd(t_parser *prog)
{
	char	buff[100];

	prog = NULL;
	getcwd(buff, sizeof(buff));
	write(var->fd_out, buff, ft_strlen(buff));
	write(var->fd_out, "\n", 1);
	if (var->fd_out > 1)
		close(var->fd_out);
}