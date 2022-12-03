/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 04:05:20 by nel-brig          #+#    #+#             */
/*   Updated: 2022/12/03 04:05:21 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"

char	*get_join(t_data *data)
{
	char	*join;

	join = NULL;
	if (data->expand == NULL && data->dollar != NULL)
		join = ft_strdup(data->dollar);
	else
		join = creat_new_string(data->dollar, data->expand);
	return (join);
}

char	*digit_case(t_lexer *lexer, t_data *data)
{
	char	*join;

	join = NULL;
	skip_first_digit(lexer);
	join = ft_strdup_and_free(data->dollar);
	free(data);
	return (join);
}

char	*get_join_and_free(t_data *data)
{
	char	*join;

	join = NULL;
	if (data->join != NULL)
		join = ft_strdup_and_free(data->join);
	free_all(data->str, data->dollar, data->expand, data);
	return (join);
}
