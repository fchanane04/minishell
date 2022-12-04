/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 04:15:29 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/03 21:41:28 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	change_pwd(t_env **env, char *pwd, char *type)
{
	t_env	*tmp;
	char	*new_line;
	char	*typ;
	int		i;

	tmp = *env;
	i = 0;
	typ = ft_strjoin_exec(type, "=");
	new_line = ft_strjoin_exec(typ, pwd);
	free(typ);
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
	var->status = -101;
}

void	var_not_set(void)
{
	ft_putstr_fd("bash: cd: HOME not set\n", 2);
	var->status = 1;
}

void	reset_cd_status(int stat)
{
	if (stat == -101)
		var->status = 1;
	else
		var->status = 0;
}

void	ft_cd(t_parser	*prog)
{
	int		stat;
	char	*line;

	if (!getcwd(NULL, 0))
		chdir(prog->args[1]);
	else
	{
		change_pwd(&var->envc, getcwd(NULL, 0), "OLDPWD");
		if (prog->args[1])
		{
			stat = chdir(prog->args[1]);
			if (stat != 0)
				cd_error(prog->args[1]);
		}
		else
		{
			line = get_envc(var->envc, "HOME");
			if (!line)
				var_not_set();
			else
				chdir(get_envc(var->envc, "HOME"));
		}
		change_pwd(&var->envc, getcwd(NULL, 0), "PWD");
		reset_cd_status(var->status);
	}
}
