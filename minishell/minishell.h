/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:03:18 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/15 22:25:06 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer/lexer.h"

#define ERROR_MSG "syntax error near unexpected token `"

typedef struct  s_parser t_parser;

typedef struct s_file t_files;

typedef struct  s_index
{
	int	heredoc;
	int	args;
}t_index;

enum file_type{
	OUT,//0
	IN,//1
	AP,//2
	AMB,//3
};
struct s_file
{
	char	*filename;
	enum file_type type;
	t_files	*next;
};

struct s_parser
{
	char	**args;//args[0]
	char	**heredoc;
	t_files	*files;
	t_parser *next;
};

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}	t_env;

typedef struct s_global
{
	t_env	*envc;
	int		status;
}	t_global;

extern t_global *var;

char		*get_char_as_string(char c);
int			ft_strlen(char *s);
void		add_token_back(t_token **head,t_token *token);
void		quotes(t_token *head);
void		check_quotes(char *line);
t_token		*init_tab(int type, char *s);
void		delete_token(t_token **token);
void		print_tab(t_token **tab);
t_token		**get_token_as_cmd(t_token *token);
t_lexer		*init_lexer(char *line);
void		print_tokens(t_token *token);
int			get_size_of_tab(t_token *token);
void		print_struct(t_parser *cmd_table);
void		syntax_error(t_token **line);
t_parser	*parse_cmd(t_token **tab);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strlen(char *s);
char		*get_char_as_string(char c);
char		*ft_strjoin(char *s1, char *s2);
int			ft_isalnum(int c);
void		free_lexer(t_lexer *lexer);
void		ft_free_cmd_table(t_parser *cmd_table);
void		ft_free_tab(t_token **tab);
void		ft_free_tokens(t_token *token);
void		init_index(t_index *index);
void		init_args_heredoc(t_token *tab, char **s, int *i);
int			get_size_of_words(t_token *tab);
int			get_size_of_files(t_token *tab, int type);
void		assign_null(t_parser *cmd_table, t_index *index);

// t_env	*clone_env(char **env);
// void	heredoc_check(t_parser *prog);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// void	ft_putstr_fd(char *str, int fd);
// char	*ft_strdup(char *s1);
// char	*ft_substr(char *s, int start, int len);
// int		builtin_check(char *cmd);
// int		fork_check(t_parser *prog);
// void	exec_builtin(t_parser *prog, t_env **env);
// void	cd_error(char *dir);
// void	change_pwd(t_env **env, char *pwd, char *type);
// void	ft_cd(t_parser	*prog, t_env **env);
// int		check_opt(char *opt);
// void	ft_echo(t_parser *prog);
// int		lines_counter(char **str);
// t_env	*clone_env(char **env);
// char	*get_envc(t_env *env, char *var);
// void	ft_env(t_parser *prog,  t_env **env);
// void	ft_pwd(t_parser *prog);
// void	ft_unset(t_parser *prog, t_env **env);
// void	ft_export(t_parser *prog, t_env **env);
// void	print_with_quotes(char *str, int fd);
// t_env	*new_node(char *line);
// void	add_env_node(t_env **env, t_env *node);
// int		printable(char *line);


#endif