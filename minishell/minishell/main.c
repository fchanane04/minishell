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

	if (ac != 1 && !envp)
	{
		av[0] = NULL;
		exit(EXIT_SUCCESS);
	}
	token = NULL;
	tab = NULL;
	cmd_table = NULL;
	var = malloc(sizeof(t_global));
	var->envc = clone_env(envp);// hadchi mazal khasso ithet f function ==> set_var(var) hta nsaybha
	var->status = 0;
	var->fd_out = 1;
	var->fd_in = 0;
	while ((line = readline("minishell@minihell>$ ")) != NULL)
	{
		if (strcmp(line, "\0") != 0)
		{
			check_quotes(line);//don't exit
			lexer = init_lexer(line);
			token = get_token(lexer);
			if (syntax(token) != -1 && token != NULL)
			{
				tab = get_token_as_cmd(token);
				//print_tab(tab);
				cmd_table = parse_cmd(tab);
				//print_struct(cmd_table);
				heredoc_check(cmd_table);//matb9aych theydi lia functins ghir diri //
				if (!fork_check(cmd_table))
					exec_builtin(cmd_table, &var->envc);
				else
				{//hadchi rah ghir bach n testi ama rah mazal khass nzid function bach n3rf wach single ola multi cmd
					var->fd_in = open_infile(cmd_table->files);
					var->fd_out = open_outfile(cmd_table->files);//append fih chi error hnaya mli 9essemt lcode mab9aach khedam kif 9bl 
					execute_single_cmd(cmd_table);
				}
				ft_free_tokens(token);
				ft_free_tab(tab);
				ft_free_cmd_table(cmd_table);
			}
			free_lexer(lexer);
			add_history(line);
			free(line);
			// system("leaks minishell");
		}
	}
}