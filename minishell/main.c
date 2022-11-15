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
			//print_tokens(token);
			syntax(token);
			tab = get_token_as_cmd(token);
			//print_tab(tab);
			cmd_table = parse_cmd(tab);
			heredoc_check(cmd_table);
			if (!fork_check(cmd_table))
				exec_builtin(cmd_table, &var->envc);
			//print_struct(cmd_table);
		}
		add_history(line);
		free(line);
	}
}
