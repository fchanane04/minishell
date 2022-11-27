/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:32:54 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/23 12:18:57 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include <unistd.h>
#include<limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include"../minishell.h"

#define EXIT_ERR1 ": numeric argument required\n"
#define EXIT_ERR2 "too many arguments\n"

typedef struct  s_parser t_parser;

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
