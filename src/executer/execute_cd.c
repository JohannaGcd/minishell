/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 21:46:54 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/15 11:10:52 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	exec_cd(char **command_args, t_minishell *mshell)
{
	char	*path;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		mshell->old_pwd = ft_strdup(cwd);
		if (find_env_var(mshell->envs, "PWD")
			&& find_env_var(mshell->envs, "OLDPWD"))
			change_env_var(mshell->envs, "OLDPWD", cwd);
	}
	path = command_args[1];
	if (path == NULL)
	{
		path = get_env_var(mshell->envs, "HOME");
		if (path == NULL)
		{
			perror("cd: HOME not set");
			return ;
		}
	}
	if (chdir(path) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			if (find_env_var(mshell->envs, "PWD"))
				change_env_var(mshell->envs, "PWD", cwd);
			free(mshell->pwd);
			mshell->pwd = ft_strdup(cwd);
		}
		else
			perror("getcwd failed");
	}
	else
		perror("cd failed");
}
