/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_start.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:53:36 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/29 12:55:46 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"

int	init_mshell(t_minishell *mshell, char **envp)
{
	t_envs	*env;

	env = (t_envs *)malloc(sizeof(t_envs));
	if (env == NULL)
	{
		perror("Failed to allocate memory for envs");
		return (0);
	}
	if (init_env(envp, env) == 0)
		return (0);
	mshell->envs = env;
	mshell->input_str = NULL;
	mshell->commands = NULL;
	mshell->tokens = NULL;
	mshell->is_exit = 0;
	return (1);
}

int	init_pwd(t_minishell *mshell)
{
	char	*pwd;

	pwd = get_env_var(mshell->envs, "PWD");
	if (pwd)
	{
		mshell->pwd = ft_strdup(pwd);
		if (mshell->pwd == NULL)
		{
			ft_putendl_fd("error malloc memory", 2);
			return (0);
		}
	}
	else
		mshell->pwd = NULL;
	return (1);
}

int	init_old_pwd(t_minishell *mshell)
{
	char	*old_pwd;

	old_pwd = get_env_var(mshell->envs, "OLDPWD");
	if (old_pwd)
	{
		mshell->old_pwd = ft_strdup(old_pwd);
		if (mshell->old_pwd == NULL)
		{
			ft_putendl_fd("error malloc memory", 2);
			return (0);
		}
	}
	else
		mshell->old_pwd = NULL;
	return (1);
}

t_msh_state	mshell_start(t_minishell *mshell, char **envp)
{
	if (init_mshell(mshell, envp) == 0)
		return (MSH_EXIT);
	if (init_pwd(mshell) == 0 || init_old_pwd(mshell) == 0)
		return (MSH_EXIT);
	return (MSH_READLINE);
}

t_msh_state	mshell_readline(t_minishell *mshell, int *exit_status)
{
	const char	prompt[] = "minishell>";

	(void) exit_status;
	rl_on_new_line();
	rl_catch_signals = 0;
	mshell->input_str = readline(prompt);
	if (!mshell->input_str)
	{
		*exit_status = 1;
		return (MSH_CLEAN);
	}
	if (ft_strncmp(mshell->input_str, "", 2) == 0)
		return (MSH_READLINE);
	if (*mshell->input_str)
		add_history(mshell->input_str);
	return (MSH_LEXER);
}
