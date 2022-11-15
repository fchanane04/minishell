#include "lexer/lexer.h"
#include "minishell.h"

void print_tokens(t_token *token)
{
    // if (token == NULL)
    //     printf("yes\n");
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
	// printf("asdfghjk\n");
	// if (cmd_table == NULL)
	// 	printf("cmd table == NULL\n");
	while (cmd_table != NULL)
	{
		printf("--------outfiles-------\n\n");
		print_data(cmd_table->out_files, "outfiles");
		printf("--------infiles--------\n\n");
		print_data(cmd_table->in_files, "infiles");
		printf("--------heredoc---------\n\n");
		print_data(cmd_table->heredoc, "heredoc");
		printf("--------append---------\n\n");
		print_data(cmd_table->append, "append");
		printf("--------cmd------------\n\n");
		printf("cmd == %s\n", cmd_table->cmd);
		printf("--------args-----------\n\n");
		print_data(cmd_table->args, "args");
		printf("========next===========\n\n");
		cmd_table = cmd_table->next;
	}
// 	if (cmd_table->out_files == NULL)
// 		printf("yes\n");
}