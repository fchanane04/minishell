#include "../lexer/lexer.h"
#include "../minishell.h"

void	ft_free_tokens(t_token *token)
{
	while (token != NULL)
	{
		free(token->value);
		token->value = NULL;
		free(token);
		token = token->next;
	}
}

void	ft_free_tab(t_token **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_free_tokens(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}

void	ft_free_cmd_table(t_parser *cmd_table)
{
	while (cmd_table != NULL)
	{
		if (cmd_table->cmd != NULL)
			free(cmd_table->cmd);
		if (cmd_table->append != NULL)
			free_tab(cmd_table->append);
		if (cmd_table->heredoc != NULL)
			free_tab(cmd_table->heredoc);
		if (cmd_table->in_files != NULL)
			free_tab(cmd_table->in_files);
		if (cmd_table->out_files != NULL)
			free_tab(cmd_table->out_files);
		if (cmd_table->args != NULL)
			free_tab(cmd_table->args);
		free(cmd_table);
		cmd_table = cmd_table->next;
	}
}

void	free_lexer(t_lexer *lexer)
{
	ft_free(lexer->line);
	free(lexer);
}