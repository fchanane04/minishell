#include "../lexer/lexer.h"
#include "../minishell.h"

void print_tokens(t_token *token)
{
    if (token->value == NULL)
	{
        printf("token value == NULL\n");
		return;
	}
    while (token != NULL)
    {
        printf("token == (%d,%s,%d)\n", token->type, token->value, token->index);
        token = token->next;
    }

}

void	print_tab(t_token **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("tab number %d\n", i);
		print_tokens(tab[i]);
		i++;
		printf("=========\n");
	}
}

void	print_data(char **s, char *str)
{
	int	i;

	i = 0;
	if (s == NULL)
		printf("         NULL\n");
	while (s != NULL && s[i] != NULL)
		printf("%s == %s\n", str, s[i++]);
}

void	print_struct(t_parser *cmd_table)
{
	int	i;

	i = 0;
	while (cmd_table != NULL)
	{
		printf("\033[1;31m--------outfiles-------\n\n");
		print_data(cmd_table->out_files, "outfiles");
		printf("\033[1;31m--------infiles--------\n\n");
		print_data(cmd_table->in_files, "infiles");
		printf("\033[1;32m--------herdoc---------\n\n");
		print_data(cmd_table->heredoc, "herdoc");
		printf("\033[1;32m--------append---------\n\n");
		print_data(cmd_table->append, "append");
		printf("\033[1;35m--------cmd------------\n\n");
		printf("cmd == %s\n", cmd_table->cmd);
		printf("\033[1;35m--------args-----------\n\n");
		print_data(cmd_table->args, "args");
		printf("\033[1;37m=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=next=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=\n\n");
		cmd_table = cmd_table->next;
	}
}