/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 21:46:54 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/16 14:02:54 by jguacide      ########   odam.nl         */
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
		{
			return (perror("Error: HOME not set"));
		}
			
	}
	if (chdir(path) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			refresh_pwd_vars(mshell, cwd);
		else
		{
			mshell->envs->status = 1;
			perror("getcwd failed");
		}	
	}
	else
	{
		mshell->envs->status = 1;
		perror("cd failed");
	}
		
}
