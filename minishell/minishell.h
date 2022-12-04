/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:03:18 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/04 00:07:09 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lexer/lexer.h"

# define ERROR_MSG "syntax error near unexpected token `"
# define EXIT_ERR1 ": numeric argument required\n"
# define EXIT_ERR2 "too many arguments\n"
# define BASH_ERR "bash: "
# define DIR_ERR ": Is a directory\n"

typedef struct s_parser	t_parser;

typedef struct s_file	t_files;

struct s_file
{
	char			*filename;
	enum e_type		type;
	int				flag;
	t_files			*next;
};

struct s_parser
{
	char		**args;
	t_files		*files;
	t_parser	*next;
};

typedef struct s_env
{
	char			*line;
	int				blacklisted;
	struct s_env	*next;
}	t_env;

typedef struct s_global
{
	t_env	*envc;
	int		fd_in;
	int		fd_out;
	int		status;
	int		flag;
}	t_global;

typedef struct s_heredoc
{
	char	*line;
	char	*name;
	char	**save;
	int		pid;
	int		fd;
}	t_heredoc;

extern t_global	*var;

void		add_token_back(t_token **head, t_token *token);
void		quotes(t_token *head);
int			check_quotes(char *line);
void		delete_token(t_token **token);
void		print_tab(t_token **tab);
t_token		**get_token_as_cmd(t_token *token);
t_lexer		*init_lexer(char *line);
void		print_tokens(t_token *token);
int			get_size_of_tab(t_token *token);
void		print_struct(t_parser *cmd_table);
t_parser	*parse_cmd(t_token **tab);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strlen(char *s);
void		free_lexer(t_lexer *lexer);
void		ft_free_cmd_table(t_parser *cmd_table);
void		ft_free_tab(t_token **tab);
void		ft_free_tokens(t_token *token);
void		init_args(t_token *tab, char **s, int *i);
int			get_size_of_words(t_token *tab);
int			get_size_of_files(t_token *tab, int type);
void		assign_null(t_parser *cmd_table, int *index);
void		add_and_free_line(char *line);
t_files		*fill_files(t_token *tab);
int			is_redirection(t_token *token);
int			check_dollar(t_lexer *lexer);
char		*whithout_expand(t_lexer *lexer);

//*******************************************************************

t_env		*clone_env(char **env);
char		*get_envc(t_env *env, char *var);
t_env		*new_node(char *line);
void		add_env_node(t_env **env, t_env *node);
void		exec_builtin(t_parser *prog, char *heredoc);
void		change_pwd(t_env **env, char *pwd, char *type);
void		cd_error(char *dir);
void		ft_cd(t_parser	*prog);
int			check_opt(char *opt);
void		ft_echo(t_parser *prog);
int			lines_counter(char **str);
int			printable(char *line);
void		ft_env(t_parser *prog);
int			check_limits(char *arg);
int			is_valid_num(char *arg);
void		exit_error(char *arg, char *error);
void		ft_exit(t_parser *prog);
void		print_with_quotes(char *str, int fd);
int			ft_strcmp(char *s1, char *s2);
int			exist_in_env(char *arg, t_env **env);
void		update_var(char *arg, t_env **env);
void		ft_export(t_parser *prog);
void		ft_pwd(t_parser *prog);
int			valid_name(char *str);
void		identifier_error(char *str, char *builtin);
void		ft_unset(t_parser *prog);
int			builtin_check(char *cmd);
int			fork_check(t_parser *prog);
char		**create_paths(t_env *env);
char		*find_path(char **paths, char *cmd);
char		**duplicate(t_env *env);
void		free_paths(char **paths);
void		exec_single_cmd(t_parser *prog, char *heredoc);
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
int			check_space(char *expand);
void		ft_execute(t_parser *prog);
int			exec_type_check(t_parser *prog);
int			list_counter(t_parser *prog);
char		**ft_heredoc(t_parser *prog);
char		*ft_strjoin_exec(char *s1, char *s2);
char		*heredoc_save(int fd, char *name);
void		write_in_heredoc(t_heredoc *hd, char *filename);
char		*heredoc_name(int i);
int			amb_red_handler(char *filename);
void		error_printer(char *bef, char *aft, char *filename);
int			isdir(char *fileName);
int			infile_handler(char *filename);
int			outfile_handler(char *filename);
int			append_handler(char *filename);
int			file_prep(t_parser *prog, char *heredoc);
int			re_init_heredoc(char *heredoc, int fd_in, int err);
void		cleanup_fd(void);
void		signal_handler(int sig);
void		signal_heredoc(int sig);
void		sig_child(int sig);
int			ft_isalpha(int c);
void		ft_builtins(t_parser *prog);
void		exec_multi_cmd(t_parser *prog, char **heredocs);
char		**ft_split_exec(char *s, char c);
void		set_status_with_error(char *arg, char *msg, int stat);
int			all_printed(t_env *envc);
int			env_counter(t_env *envc);
char		**export_stock(void);
void		export_printer(char **stock);
int			find_equal(char *str);
int			ft_strcmp_export(char *s1, char *s2);
char		*var_name(char *line);
void		print_export(char **stock);
int			still_heredoc(t_files *file);
void		fd_closer(void);
int			open_and_write(char *filename, char *name);
int			check_other_heredoc(t_files *file);
char		*save_in(char *name);
void		var_not_set(void);
void		export_var(char *arg);
void		add_to_end(char *arg);
void		add_or_update(char *arg);
int			last_check(char *arg);
void		add_without_plus(char *arg);
void		directory_error(char *arg);
void		permission_error(char *arg);
void		not_found_error(char *arg);
int			valid_name_exp(char *str);
void		remove_inside(char *arg);
char		*arr_create(char *arg);
void		heredoc_handler(void);
void		reset_cd_status(int stat);
void		cmd_error_check(char *arg, char *path);
void		no_directory(char *arg);
int			last_with_back(char *arg);
int			is_file(char *arg);
void		file_error(char *arg);
void		exit_status(pid_t pid);
int			loop_on_heredocs(t_files *file, char *name);
void		signal_before(void);
void		signal_in(void);
void		ft_dup_in_single(void);
void		set_used_vars(void);

#endif