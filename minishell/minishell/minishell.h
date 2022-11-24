/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:03:18 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/23 12:49:05 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer/lexer.h"

#define ERROR_MSG "syntax error near unexpected token `"
#define EXIT_ERR1 ": numeric argument required\n"
#define EXIT_ERR2 "too many arguments\n"

// LOL
int	*exit_status_setter(int stat);

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
	int		fd_in;
	int		fd_out;
	int		status;
}	t_global;

extern t_global *var;

char		*get_char_as_string(char c);
int			ft_strlen(char *s);
void		add_token_back(t_token **head,t_token *token);
void		quotes(t_token *head);
int			check_quotes(char *line);
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
void		add_and_free_line(char *line);

//*******************************************************************

t_env		*clone_env(char **env);
char		*get_envc(t_env *env, char *var);
t_env		*new_node(char *line);
void		add_env_node(t_env **env, t_env *node);
void		exec_builtin(t_parser *prog, t_env **env);
void		change_pwd(t_env **env, char *pwd, char *type);
void		cd_error(char *dir);
void		ft_cd(t_parser	*prog, t_env **env);
int			check_opt(char *opt);
void		ft_echo(t_parser *prog);
int			lines_counter(char **str);
int			printable(char *line);
void		ft_env(t_parser *prog, t_env **env);
int			check_limits(char *arg);
int			is_valid_num(char *arg);
void		exit_error(char *arg, char *error);
void		ft_exit(t_parser *prog);
void		print_with_quotes(char *str, int fd);
int			ft_strcmp(char *s1, char *s2);
int			exist_in_env(char *arg, t_env **env);
void		update_var(char *arg, t_env **env);
void		ft_export(t_parser *prog, t_env **env);
void		ft_pwd(t_parser *prog);
int			valid_name(char *str);
void		unset_error(char *str);
void		ft_unset(t_parser *prog, t_env **env);
int			builtin_check(char *cmd);
int			fork_check(t_parser *prog);
char		**create_paths(t_env *env);
char		*find_path(char **PATHS, char *cmd);
char		**duplicate(t_env *env);
void		free_paths(char **paths);
void		execute_single_cmd(t_parser *prog);
void		heredoc_check(t_parser *prog);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *str, int fd);
char		*ft_strdup(char *s1);
char		*ft_substr(char *s, int start, int len);
long long	ft_atoi(char *str);
char		**ft_split(char	*s, char c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
char		*ft_strjoin_mod(char *s1, char *s2);
void		leaks_hunter(char ***str);
int			open_infile(t_files *files);
int			open_outfile(t_files *files);
int			ft_isalnum(int c);

#endif