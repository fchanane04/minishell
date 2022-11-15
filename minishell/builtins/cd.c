/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:23:42 by fchanane          #+#    #+#             */
/*   Updated: 2022/11/15 10:04:33 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	change_pwd(t_env **env, char *pwd, char *type)
{
	t_env	*tmp;
	char	*new_line;
	int		i;

	tmp = *env;
	i = 0;
	new_line = ft_strjoin(type, "=");
	new_line = ft_strjoin(new_line, pwd);
	while (tmp)
	{
		if (!ft_strncmp(tmp->line, type, ft_strlen(type)))
			tmp->line = ft_strdup(new_line);
		tmp = tmp->next;
	}
	free(new_line);
}

void	cd_error(char *dir)
{
	ft_putstr_fd("bash: cd: ", 1);
	ft_putstr_fd(dir, 1);
	ft_putstr_fd(": ", 1);
	perror("");
}

void	ft_cd(t_parser	*prog, t_env **env)
{
	int		stat;
	char	buff[100];

	change_pwd(env, getcwd(buff, sizeof(buff)), "OLDPWD");
	if (prog->args[1])
	{
		stat = chdir(prog->args[1]);
		if (stat != 0)
			cd_error(prog->args[1]);
	}
	else
		chdir(get_envc(*env, "HOME"));
	change_pwd(env, getcwd(buff, sizeof(buff)), "PWD");
}