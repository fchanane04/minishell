#include "lexer/lexer.h"
#include "minishell.h"

t_global	*var;

void	ft_free_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token != NULL)
	{
		free(token->value);
		token->value = NULL;
		token = token->next;
	}
	free(token);
	token = NULL;
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
	free(lexer->line);
	free(lexer);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_lexer	*lexer;
	t_token	*token;
	t_token	**tab;
	t_parser *cmd_table;
	char	*s;

	if (ac != 1)
	{
		av[0] = NULL;
		exit(EXIT_SUCCESS);
	}
	token = NULL;
	tab = NULL;
	cmd_table = NULL;
	s = NULL;
	var = malloc(sizeof(t_global));
	var->envc = clone_env(envp);
	var->status = 0;
	while ((line = readline("minishell@minihell>$ ")) != NULL)
	{
		if (strcmp(line, "\0") != 0)
		{
			check_quotes(line);
			lexer = init_lexer(line);
			token = get_token(lexer, envp);
			if (syntax(token) != -1)
			{
				tab = get_token_as_cmd(token);
				print_tab(tab);
				cmd_table = parse_cmd(tab); 
				print_struct(cmd_table);
				ft_free_tokens(token);
				ft_free_tab(tab);
			}
		}
		// free_lexer(lexer);
		// ft_free_cmd_table(cmd_table);
		add_history(line);
		free(line);
		// system("leaks minishell");
	}
}
