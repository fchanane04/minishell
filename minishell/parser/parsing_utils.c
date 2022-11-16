#include "../lexer/lexer.h"
#include "../minishell.h"

int	get_size_of_files(t_token *tab, int type)
{
	int	count;

	count = 0;
	while (tab != NULL)
	{
		if ((int)tab->type == type)
			count++;
		tab = tab->next;
	}
	return(count);
}

int	get_size_of_words(t_token *tab)
{
	int count;

	count = 0;
	while (tab != NULL)
	{
		if (tab->type == R_RED || tab->type == L_RED || tab->type == DEL || tab->type == APP)
		{
			tab = tab->next;
			if(tab == NULL)
				break;
		}
		else if (tab->type == WORD)
			count++;
		tab = tab->next;
	}
	return(count);
}

void	init_file(t_token *tab, char **file, int *i)
{
	if (tab->value != NULL)
		file[*i] = strdup(tab->value);
	else
		file[*i] = NULL;
	*i += 1;
	
}

void	init_index(t_index *index)
{
	index->append  = 0;
	index->args = 0;
	index->heredoc = 0;
	index->infile = 0;
	index->outfile = 0;
}

void	assign_null(t_parser *cmd_table, t_index *index)
{
	if(cmd_table->args != NULL)
		cmd_table->args[index->args] = NULL;
	if(cmd_table->in_files != NULL)
		cmd_table->in_files[index->infile] = NULL;
	if(cmd_table->out_files != NULL)
		cmd_table->out_files[index->outfile] = NULL;
	if(cmd_table->heredoc != NULL)
		cmd_table->heredoc[index->heredoc] = NULL;
	if(cmd_table->append != NULL)
		cmd_table->append[index->append] = NULL;
	cmd_table->next = NULL;
}
