/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_start.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:53:36 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/14 10:16:58 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"

t_msh_state	mshell_start(t_minishell *mshell, char **envp)
{
	t_envs	*env;

	env = (t_envs *)malloc(sizeof(t_envs));
	//printf("debug START\n");
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

t_msh_state	mshell_readline(t_minishell *mshell, int *exit_status)
{
	
	const char	prompt[] = "minishell:";
	(void) exit_status;
	//printf("debug READLINE\n");
	//fflush(stdout);
	rl_on_new_line();
	//rl_replace_line("", 0);
	//rl_redisplay();
	mshell->input_str = readline(prompt);
	printf("Readline returned: %s\n", mshell->input_str ? mshell->input_str : "NULL");
	if (!mshell->input_str)
	{
		*exit_status = 1;
		printf("\nwe are here\n");
		return (MSH_CLEAN);
	}
	if (ft_strncmp(mshell->input_str, "", 2) == 0)
		return (MSH_READLINE);
	if (*mshell->input_str)
		add_history(mshell->input_str);
	return (MSH_LEXER);
}
