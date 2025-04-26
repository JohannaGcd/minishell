/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_msh_start.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:53:36 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/26 08:57:52 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"

t_msh_state	fn_msh_start(t_minishell *mshell, char **envp)
{
	t_envs	*env;

	env = (t_envs *)malloc(sizeof(t_envs));
	printf("debug START\n");
	if (env == NULL)
	{
		perror("Failed to allocate memory for envs");
		return (MSH_EXIT);
	}
	init_env(envp, env);
	mshell->envs = env;
	mshell->input_str = NULL;
	mshell->commands = NULL;
	mshell->tokens = NULL;
	mshell->isExit = 0;
	return (MSH_READLINE);
}

t_msh_state	fn_msh_readline(t_minishell *mshell)
{
	const char	prompt[] = "minishell > ";

	printf("debug READLINE\n");
	mshell->input_str = readline(prompt);
	if (!mshell->input_str)
		return (MSH_CLEAN);
	if (*mshell->input_str)
		add_history(mshell->input_str);
	return (MSH_LEXER);
}
