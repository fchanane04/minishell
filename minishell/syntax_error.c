/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:06:55 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/01 16:27:57 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer/lexer.h"
#include"minishell.h"

void	error_msg(char *msg, char *token)
{
	printf("bash: %s%s\'", msg, token);
	exit(1);
}

void	error_pipe(t_token *token)
{
	if (token->index == 0)
		error_msg(ERROR_MSG, token->value);
	else if (token->next == NULL)
		error_msg(ERROR_MSG, "newline");
	else if (token->next->type == PIPE)
		error_msg(ERROR_MSG, token->value);
}

void	error(t_token *token)
{	int	type;

	if (!token->next)
		error_msg(ERROR_MSG, "newline");
	type = token->next->type;
	if (type == PIPE || type == R_RED || type == L_RED || type == APP || type == DEL)
		error_msg(ERROR_MSG, token->next->value);
}

void	error_left_redirection(t_token *token)
{
	int	type;

	if (!token->next)
		error_msg(ERROR_MSG, "newline");
	type = token->next->type;
	if (type == PIPE || type == L_RED || type == APP || type == DEL)
		error_msg(ERROR_MSG, token->next->value);
}

void	syntax(t_token *token)
{
	while (token != NULL)
	{
		if(token->type == PIPE)
			error_pipe(token);
		else if (token->type == R_RED)
			error(token);
		else if (token->type == L_RED)
			error_left_redirection(token);
		else if(token->type == DEL)
			error(token);
		else if (token->type == APP)
			error(token);
		token = token->next;
	}
}