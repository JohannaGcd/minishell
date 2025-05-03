/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_clean.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:49:27 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/03 19:20:27 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "executer.h"

void free_redirection(t_redirection	*redirections)
{
	t_redirection *current;
	t_redirection *next;

	current = redirections;
	while (current) {
		next = current->next;
		if (current->file)
			free(current->file);
		if (current->fd >= 0)
			close(current->fd);
		free(current); 
		current = next;
	}
}

void clean_commands(t_command *commands)
{
	t_command *current;
	t_command *next;
	int i;

	current = commands;
	while (current) {
		next = current->next;
		if (current->command_args) {
			for (i = 0; current->command_args[i]; i++)
				free(current->command_args[i]);
			free(current->command_args);
		}
		if (current->in)
			free_redirection(current->in);
		if (current->out)
			free_redirection(current->out);
		free(current);
		current = next;
	}
}

t_msh_state	mshell_clean(t_minishell *mshell)
{
	//printf("debug CLEAN\n");
	if (mshell->input_str)
	{
		free(mshell->input_str);
		mshell->input_str = NULL;
	}
	if (mshell->tokens)
	{
		clean_tokens(mshell->tokens);
		mshell->tokens = NULL;
	}
	if (mshell->commands)
	{
		clean_commands(mshell->commands);
		mshell->commands = NULL;
	}
	if (mshell->envs)
	{
		clean_env(&(mshell->envs));
		mshell->envs = NULL;
	}
	return (MSH_EXIT);
}
