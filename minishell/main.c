#include "lexer/lexer.h"
#include "minishell.h"

t_global	*var;



int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_lexer	*lexer;
	t_token	*token;
	t_token	**tab;
	t_parser *cmd_table;

	if (ac != 1)
	{
		av[0] = NULL;
		exit(EXIT_SUCCESS);
	}
	token = NULL;
	tab = NULL;
	cmd_table = NULL;
	var = malloc(sizeof(t_global));
	var->envc = clone_env(envp);
	var->status = 124;
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
				// print_tab(tab);
				cmd_table = parse_cmd(tab);
				print_struct(cmd_table);
				ft_free_tokens(token);
				ft_free_tab(tab);
				ft_free_cmd_table(cmd_table);
			}
			free_lexer(lexer);
			add_history(line);
			free(line);
			system("leaks minishell");
		}
	}
}
