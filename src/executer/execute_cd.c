/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 21:46:54 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/16 15:55:30 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static void	refresh_pwd_vars(t_minishell *mshell, char *cwd)
{
	if (find_env_var(mshell->envs, "PWD"))
		change_env_var(mshell->envs, "PWD", cwd);
	free(mshell->pwd);
	mshell->pwd = ft_strdup(cwd);
}

void	exec_cd(char **command_args, t_minishell *mshell)
{
	char	*path;
	char	cwd[PATH_MAX];

	mshell->envs->status = 0;
	if (command_args[1] && command_args[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		mshell->envs->status = 1;
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		free(mshell->old_pwd);
		mshell->old_pwd = ft_strdup(cwd);
		if (find_env_var(mshell->envs, "PWD")
			&& find_env_var(mshell->envs, "OLDPWD"))
			change_env_var(mshell->envs, "OLDPWD", cwd);
	}
	if (command_args[1])
		path = command_args[1];
	else
	{
		path = get_env_var(mshell->envs, "HOME");
		if (path == NULL)
			return (perror("cd: HOME not set"));
	}
	if (chdir(path) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			refresh_pwd_vars(mshell, cwd);
		else
		{
			perror("getcwd failed");
			mshell->envs->status = 1;
		}
	}
	else
	{
		perror("cd failed");
		mshell->envs->status = 1;
	}
}
