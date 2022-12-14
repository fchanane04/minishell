#include "lexer/lexer.h"
#include "minishell.h"

t_global	*var;

void	free_lexer(t_lexer *lexer)
{
	free(lexer->line);
	lexer->line = NULL;
	free(lexer);
}

void	free_all_struct(t_token *token, t_token **tab, t_parser *cmd_table)
{
	ft_free_tokens(token);
	ft_free_tab(tab);
	ft_free_cmd_table(cmd_table);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_lexer		*lexer;
	t_token		*token;
	t_token		**tab;
	t_parser	*cmd_table;
	int		ret;
	int		quotes;

	if (ac != 1 && !envp)
	{
		av[0] = NULL;
		exit(EXIT_SUCCESS);
	}
	token = NULL;
	tab = NULL;
	cmd_table = NULL;
	ret = 0;
	quotes = 0;
	var = malloc(sizeof(t_global));
	var->envc = clone_env(envp);
	var->status = 0;
	var->fd_out = 1;
	var->fd_in = 0;
	
	signal(SIGINT, signal_handler);
	while (1)
	{
		var->flag = 0;
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);

		line = readline("minishell$> ");

		if (line == 0x0)
		{
			printf("exit\n");
			exit(var->status);
		}
		if (strcmp(line, "\0") != 0)
		{
			quotes = check_quotes(line);
			if (quotes == -1)
			{
				var->status = 258;
				add_and_free_line(line);
				continue;
			}
			lexer = init_lexer(line);
			token = get_token(lexer);
			ret = syntax(token);
			if (ret == -1)
			{
				var->status = 258;
				add_and_free_line(line);
				free_lexer(lexer);
				ft_free_tokens(token);
				continue;
			}
			if (token != NULL)
			{
				tab = get_token_as_cmd(token);
				cmd_table = parse_cmd(tab);
				ft_execute(cmd_table);
								//print_struct(cmd_table);
				free_all_struct(token, tab, cmd_table);
			}
			free_lexer(lexer);
			add_and_free_line(line);
			//system("leaks minishell");
		}
	}
}