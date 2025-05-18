/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 21:46:54 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/18 12:30:59 by sveta         ########   odam.nl         */
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

bool	check_arg_count(char **command_args, t_minishell *mshell)
{
	if (command_args[1] && command_args[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		mshell->envs->status = 1;
		return (1);
	}
	return (0);
}

void	change_old_path(char *path, t_minishell *mshell)
{
	free(mshell->old_pwd);
	mshell->old_pwd = ft_strdup(path);
	if (find_env_var(mshell->envs, "PWD")
		&& find_env_var(mshell->envs, "OLDPWD"))
		change_env_var(mshell->envs, "OLDPWD", path);
}

void	change_dir(char *path, char *old_path, t_minishell *mshell)
{
	char	cwd[PATH_MAX];

	if (chdir(path) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			refresh_pwd_vars(mshell, cwd);
			change_old_path(old_path, mshell);
		}
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

void	exec_cd(char **command_args, t_minishell *mshell)
{
	char	*path;
	char	cwd[PATH_MAX];
	char	*old_path;

	mshell->envs->status = 0;
	if (check_arg_count(command_args, mshell) == 1)
		return ;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		old_path = ft_strdup(cwd);
	if (command_args[1])
		path = command_args[1];
	else
	{
		path = get_env_var(mshell->envs, "HOME");
		if (path == NULL)
			return (ft_putendl_fd("Error: HOME not set", 2));
	}
	change_dir(path, old_path, mshell);
}
