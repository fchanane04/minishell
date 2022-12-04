/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:56:50 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/03 12:04:44 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	directory_error(char *arg)
{
	var->status = 126;
	printf("bash: %s: is a directory\n", arg);
	exit(var->status);
}

void	permission_error(char *arg)
{
	printf("bash: %s: Permission denied\n", arg);
	var->status = 126;
	exit(var->status);
}

void	not_found_error(char *arg)
{
	var->status = 127;
	printf("bash: %s: command not found\n", arg);
	exit(var->status);
}

void	no_directory(char *arg)
{
	if (is_file(arg))
		file_error(arg);
	else
	{
		var->status = 127;
		printf("bash: %s: No such file or directory\n", arg);
		exit(var->status);
	}	
}

void	file_error(char *arg)
{
	var->status = 126;
	printf("bash: %s: Not a directory\n", arg);
	exit(var->status);
}
