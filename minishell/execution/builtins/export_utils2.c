/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:04:25 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/02 16:05:06 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

char	*arr_create(char *arg)
{
	char	**split;
	char	*arr;

	split = ft_split_exec(arg, '+');
	arr = ft_strdup(split[0]);
	leaks_hunter(&split);
	return (arr);
}
