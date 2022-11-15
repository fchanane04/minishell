#include "lexer/lexer.h"

int	skip(char *line, char c)
{
	int i;

	i = 0;
	while (line[i] != c && line[i] != '\0')
		i++;
	if (line[i] == '\0')
	{
		printf("error quotes\n");
		exit(EXIT_FAILURE);
	}
	i++;
	return(i);
}

void	check_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			if (line[i] == '"')
				i = skip(&line[i + 1], '"') + i + 1;
			else if (line[i] == '\'')
				i = skip(&line[i + 1], '\'') + i + 1;
		}
		else
			i++;
	}
}