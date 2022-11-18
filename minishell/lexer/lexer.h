#ifndef LEXER_H
# define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <fcntl.h>


typedef struct  s_lexer
{
    char c;
    int i;
    char *line;
}t_lexer;

enum type{
    R_RED,
    L_RED,
    PIPE,
    WORD,
	DEL,
	APP,
};

typedef struct  s_token t_token;

struct s_token
{
    enum type type;
    char *value;
    int index;
    t_token *next;
};


void	add_herdoc(t_lexer *lexer, t_token **token, int *flag);
t_token	*init_token(int type, char *s, int *flag);
void    add_token_back(t_token **head,t_token *new);
void    quotes(t_token *head);
void	check_quotes(char *line);
t_token *init_tab(int type, char *s);
void	delete_token(t_token **token);
void	print_tab(t_token **tab);
t_token	**get_token_as_cmd(t_token *token);
t_lexer	*init_lexer(char *line);
void	print_tokens(t_token *token);
t_token	*get_token(t_lexer *lexer, char **envp);
int		get_size_of_tab(t_token *token);
int		ft_isalnum(int c);
void	lexer_advance(t_lexer *lexer);
char	*get_str_inside_quotes(t_lexer *lexer, char **envp);
void    add_token_back(t_token **token,t_token *new);
t_token *init_token(int type, char *s, int *flag);
void	delete_token(t_token **token);
char	*single_quote(t_lexer *lexer);
char	*double_quote(t_lexer *lexer, char **envp);
char	*collect_string_check_dollar(t_lexer *lexer, char **envp);
char	*expand_dollar(t_lexer *lexer, char **envp);
int		syntax(t_token *token);
void	error_msg(char *msg, char *token);
void	ft_skip_whitespaces(t_lexer *lexer);
void	lexer_advance(t_lexer *lexer);
int		special_characters(char c);
int		red_or_pipe(char c);
t_lexer	*init_lexer(char *line);
void	ft_free(char *s);
char    *get_env(char *str, char **envp);
char	*dollar(t_lexer *lexer, char **envp);
char	*ft_itoa(int n);
void	skip(t_lexer *lexer, char c);

#endif
