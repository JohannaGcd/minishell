/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 13:52:31 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/08 22:14:50 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void execute_single_command(t_command *command)
{
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) 
	{
		// Child process
		handle_exe_redirections(command);
		if (execvp(command->command_args[0], command->command_args) == -1) 
		{
			perror("execvp failed");
			exit(EXIT_FAILURE);
		}
	} 
	else 
	{
		// Parent process
		int status;
		waitpid(pid, &status, 0);
	}
}

void execute_commands(t_minishell *mshell) 
{
	t_command   *current;
	current = mshell->commands;
	
	while (current) 
	{   
		if (ft_strncmp(current->command_args[0],"export", 7) == 0)
			exec_export(current, mshell);
		else if (ft_strncmp(current->command_args[0],"env", 4) == 0)
			exec_env(mshell);
		else
			execute_single_command(current);
		current = current->next;
	}
}
