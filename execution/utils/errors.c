/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:56:50 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/02 11:01:57 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	directory_error(char *arg)
{
	var->status = 126;
	printf("bash: %s: is a directory\n", arg);
}

void	permission_error(char *arg)
{
	printf("bash: %s: Permission denied\n",arg);
	var->status = 126;
}

void	not_found_error(char *arg)
{
	var->status = 127;
	printf("bash: %s: command not found\n", arg);
	exit(var->status);
}
