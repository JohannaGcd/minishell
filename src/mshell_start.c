/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_start.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:53:36 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/19 17:13:33 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"

t_msh_state	mshell_start(t_minishell *mshell, char **envp)
{
	t_envs	*env;

	env = (t_envs *)malloc(sizeof(t_envs));
	if (env == NULL)
	{
		perror("Failed to allocate memory for envs");
		return (MSH_EXIT);
	}
	init_env(envp, env);
	//debug
	//printf("debug\n");
	//end debug
	mshell->envs = env;
	mshell->input_str = NULL;
	mshell->commands = NULL;
	mshell->tokens = NULL;
	mshell->isExit = 0;
	mshell->pwd = ft_strdup(get_env_var(mshell->envs, "PWD"));
	mshell->old_pwd = ft_strdup(get_env_var(mshell->envs, "OLDPWD"));
	return (MSH_READLINE);
}

t_msh_state	mshell_readline(t_minishell *mshell, int *exit_status)
{
	const char	prompt[] = "minishell>";

	(void) exit_status;
	rl_on_new_line();
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
