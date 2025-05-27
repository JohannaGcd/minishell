/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_start.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:53:36 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/27 18:34:44 by spanfilo      ########   odam.nl         */
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
	init_env(envp, env);
	mshell->envs = env;
	mshell->input_str = NULL;
	mshell->commands = NULL;
	mshell->tokens = NULL;
	mshell->is_exit = 0;
	return (1);
}

t_msh_state	mshell_start(t_minishell *mshell, char **envp)
{
	char	*old_pwd;
	char	*pwd;

	if (init_mshell(mshell, envp) == 0)
		return (MSH_EXIT);
	pwd = get_env_var(mshell->envs, "PWD");
	if (pwd)
		mshell->pwd = ft_strdup(pwd);
	else
		mshell->pwd = NULL;
	old_pwd = get_env_var(mshell->envs, "OLDPWD");
	if (old_pwd)
		mshell->old_pwd = ft_strdup(old_pwd);
	else
		mshell->old_pwd = NULL;
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
