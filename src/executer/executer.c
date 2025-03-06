/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 13:52:31 by sveta         #+#    #+#                 */
/*   Updated: 2025/03/06 21:57:24 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/executer.h"

void handle_redirections(t_command *command)
{
    if (command->in)
	{
        int in_fd = open(command->in->file, O_RDONLY);
        if (in_fd == -1) {
            perror("Error opening input file");
            exit(EXIT_FAILURE);
        }
        dup2(in_fd, STDIN_FILENO); // Redirect stdin
        close(in_fd);
    }
    if (command->out)
	{
        int out_fd = open(command->out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fd == -1) {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }
        dup2(out_fd, STDOUT_FILENO); // Redirect stdout
        close(out_fd);
    }
}

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
        handle_redirections(command);
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


void execute_commands(t_command *commands) 
{
	t_command *current = commands;
	while (current != NULL) 
	{
		execute_single_command(current);
		current = current->next;
	}
}
