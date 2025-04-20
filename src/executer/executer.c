/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 13:52:31 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/20 15:27:36 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	execute_single_command(t_command *command)
{
	if (command->in->type == HEREDOC)
		handle_heredoc(command);
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) 
	{
        // Child process
		// TODO: check if here add if/else condition cause HEREDOC redirect already handled.
        open_file_redirect(command);
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
        // printf("in execute single command: redirect in is: %d with file %s\n", command->in->type, command->in->file);
        // printf("in execute single command: redirect out is: %d with file %s\n", command->out->type, command->out->file);
        waitpid(pid, &status, 0);
    }
}

void execute_commands(t_minishell *mshell) 
{
	t_command   *current;
	current = mshell->commands;
	
	while (current) 
	{  
		printf("debug current command %s\n", current->command_args[0]); 
		if (ft_strncmp(current->command_args[0],"export", 7) == 0)
			exec_export(current, mshell);
		else if (ft_strncmp(current->command_args[0],"env", 4) == 0)
			exec_env(mshell);
		else if (ft_strncmp(current->command_args[0],"unset", 6) == 0)
			exec_unset(current, mshell);
		else
			execute_single_command(current);
		current = current->next;
	}
}
