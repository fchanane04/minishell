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
	while ((line = readline("minishell@minihell>$ ")) != NULL)
	{
		if (line == 0x0)
		{
			printf("\n");
			break;
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
				print_struct(cmd_table);
				free_all_struct(token, tab, cmd_table);
			}
			free_lexer(lexer);
			add_and_free_line(line);
			// system("leaks minishell");
		}
	}
}