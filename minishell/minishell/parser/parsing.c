#include "../lexer/lexer.h"
#include "../minishell.h"

void	fill_args_herdoc(t_token *tab, t_parser *cmd_table, t_index *index)
{
	int		type;
	t_token	*tmp;

	tmp = tab;
	while (tmp != NULL)
	{
		type = tmp->type;
		if (type == DEL)
		{
			tmp = tmp->next;
			init_args_heredoc(tmp, cmd_table->heredoc, &index->heredoc);
		}
		else if (type == R_RED || type == L_RED || type == APP)
			tmp = tmp->next;
		else if (type == WORD)
			init_args_heredoc(tmp, cmd_table->args, &index->args);
		tmp = tmp->next;
	}
}

int	file_type(int type)
{
	if (type == R_RED)
		return(OUT);
	else if (type == L_RED)
		return(IN);
	else if (type == APP)
		return(AP);
	return(0);
}

t_files *init_file(t_token *tab, int type)
{
	t_files *file;

	file = malloc(sizeof(t_files));
	if (!file)
		return(NULL);
	file->type = file_type(type);
	file->filename = strdup(tab->value);
	file->next = NULL;
	return(file);
}

void	add_file_back(t_files **files, t_files *new)
{
	t_files *tmp;

	if (!*files)
	{
		*files = new;
		return ;
	}
	tmp = *files;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	t_files *fil;
	fil = *files;
	while (fil != NULL)
	{
		//printf("filename fil == |%s|\n", fil->filename);
		fil = fil->next;
	}
}

t_files	*fill_files(t_token *tab)
{
	t_token	*tmp;
	int		type;
	t_files *files;

	tmp = tab;
	files = NULL;
	while (tmp != NULL)
	{
		type = tmp->type;
		if (type == R_RED || type == L_RED || type == APP)
		{
			tmp = tmp->next;
			add_file_back(&files , init_file(tmp, type));
		}
		tmp = tmp->next;
	}
	return(files);
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
	return (s);
}

t_parser *init_cmd_table(t_token *tab)
{
	t_parser	*cmd_table;
	t_index		*index;
	int			size;

	cmd_table = malloc(sizeof(t_parser));
	if (!cmd_table)
		exit(EXIT_FAILURE);
	index = malloc(sizeof(t_index));
	if (!index)
		exit(EXIT_FAILURE);
	init_index(index);
	size = get_size_of_words(tab);
	cmd_table->args = ft_allocate(size);
	size = get_size_of_files(tab, DEL);
	cmd_table->heredoc = ft_allocate(size);
	fill_args_herdoc(tab, cmd_table, index);
	cmd_table->files = fill_files(tab);
	assign_null(cmd_table, index);
	free(index);
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
