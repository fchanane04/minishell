#include "lexer.h"

t_token *init_token(int type, char *s, int *flag)
{
    t_token *token;
    static int i;

    if (*flag == 0)
    {
        i = 0;
        *flag = 1;
    }
    token = malloc(sizeof(t_token));
    if (!token)
        exit(EXIT_FAILURE);
    token->type = type;
    token->value = strdup(s);
    token->index = i;
    token->next = NULL;
    // ft_free(s);//modifier
	
    i++;
    return(token);
}



void    add_token_back(t_token **token,t_token *new)
{
    t_token *tmp;

    if (!*token)
    {
        *token = new;
        return ;
    }

    tmp = *token;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
}

void	delete_token(t_token **token)
{
	t_token *tmp;

	tmp = *token;
	if (tmp->next == NULL)
		*token = NULL;
	while (tmp->next->next != NULL)
		tmp = tmp->next;
	if (tmp->next->next == NULL)
		tmp->next = NULL;
}
