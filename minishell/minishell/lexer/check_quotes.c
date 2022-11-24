#include "lexer.h"
#include "../minishell.h"

void	add_and_free_line(char *line)
{
	add_history(line);
	free(line);
}

int		check_quotes(char *line)
{
	int		i;
	int		ret;
	char	c;

	i = 0;
	ret = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			c = line[i];
			i++;
			while (line[i] != c && line[i] != '\0')
				i++;
			if (line[i] == '\0')
			{
				printf("syntax error\n");
				return (-1);
			}
			else if (line[i] == c)
				i++;
		}
		else
			i++;
	}
	return (0);
}