/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 01:36:23 by nel-brig          #+#    #+#             */
/*   Updated: 2022/11/29 01:36:25 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"

char	*add_ambiguous(t_token **token, char *str)
{
	
	add_token_back(token, init_token(AMB, str));
	return (NULL);
}

int	is_ambiguous(char *dollar, char *string, char *expand, t_lexer *lexer)
{
	if (dollar == NULL && string == NULL && expand == NULL)
	{
		if (is_space(lexer->c) == 0 || lexer->c == '\0')
			return (1);
	}
	return (-1);
}
