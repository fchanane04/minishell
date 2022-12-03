/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:23:04 by nel-brig          #+#    #+#             */
/*   Updated: 2022/12/03 19:23:05 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "minishell.h"

void	free_lexer(t_lexer *lexer)
{
	free(lexer->line);
	lexer->line = NULL;
	free(lexer);
}

void	free_all_struct(t_token *token, t_parser *cmd_table)
{
	ft_free_tokens(token);
	ft_free_cmd_table(cmd_table);
}

char	*ft_strdup_and_free(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

void	free_lexer_and_line(t_lexer *lexer, char *line)
{
	free_lexer(lexer);
	add_and_free_line(line);
}

void	set_status_and_free(char *line, t_token *token,
		t_lexer *lexer, int flag)
{
	var->status = 258;
	add_and_free_line(line);
	if (flag == 1)
	{
		free_lexer(lexer);
		ft_free_tokens(token);
		// printf("lexer : %p, tokens : %p\n", lexer, token);
		//print address here
	}
}
