#include "lexer/lexer.h"
#include "minishell.h"

typedef struct  s_index
{
	int	outfile;
	int	infile;
	int	heredoc;
	int	append;
	int	args;
}t_index;


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

void	fill_cmd(t_token *tab, t_parser *cmd_table)
{
	t_index	*index;
	int		type;

	index = malloc(sizeof(t_index));
	if (!index)
		exit(EXIT_FAILURE);
	init_index(index);
	while (tab != NULL)
	{
		type = tab->type;
		if (type == R_RED || type == L_RED || type == DEL || type == APP)
			tab = tab->next;
		if (type == R_RED)
			init_file(tab, cmd_table->out_files, &index->outfile);
		else if (type == L_RED)
			init_file(tab, cmd_table->in_files, &index->infile);
		else if (type == DEL)
			init_file(tab, cmd_table->heredoc, &index->heredoc);
		else if (type == APP)
			init_file(tab, cmd_table->append, &index->append);
		else if (type == WORD)
			init_file(tab, cmd_table->args, &index->args);
		tab = tab->next;
	}
	if (cmd_table->args != NULL && cmd_table->args[0] != NULL)
		cmd_table->cmd = strdup(cmd_table->args[0]);
	else
		cmd_table->cmd = NULL;
	assign_null(cmd_table, index);
}

char	**ft_allocate(int size)
{
	char	**s;

	s = NULL;
	if (size != 0)
	{
		s = malloc(sizeof(char *) * (size + 1));
		if (!s)
			exit(EXIT_FAILURE);
	}
	return(s);
}

t_parser *init_cmd_table(t_token *tab)
{
	t_parser	*cmd_table;
	int			size;

	cmd_table = malloc(sizeof(t_parser));
	if (!cmd_table)
		exit(EXIT_FAILURE);
	size  = get_size_of_files(tab, R_RED);
	cmd_table->out_files = ft_allocate(size);
	size = get_size_of_files(tab, L_RED);
	cmd_table->in_files = ft_allocate(size);
	size = get_size_of_words(tab);
	cmd_table->args = ft_allocate(size);
	size = get_size_of_files(tab, DEL);
	cmd_table->heredoc = ft_allocate(size);
	size = get_size_of_files(tab, APP);
	cmd_table->append = ft_allocate(size);
	fill_cmd(tab, cmd_table);
	return(cmd_table);
}

void	add_cmd_back(t_parser **cmd_table, t_parser *new)
{
	t_parser *tmp;

	tmp = NULL;
	if (*cmd_table == NULL)
	{
		*cmd_table = new;
		return;
	}
	tmp = *cmd_table;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	assign_to_null(t_parser *cmd_table, char *s)
{
	cmd_table->args = NULL;
	cmd_table->append = NULL;
	cmd_table->heredoc = NULL;
	cmd_table->in_files = NULL;
	cmd_table->out_files = NULL;
	cmd_table->cmd = strdup(s);
}

t_parser	*parse_cmd(t_token **tab)
{
	t_parser	*cmd_table;
	int			i;
	int			j;

	i = 0;
	j = 0;
	cmd_table = NULL;
	while (tab[i] != NULL)
	{
		add_cmd_back(&cmd_table, init_cmd_table(tab[i]));
		i++;
	}
	return(cmd_table);
}
