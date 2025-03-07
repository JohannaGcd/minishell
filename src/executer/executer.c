/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 13:52:31 by sveta         #+#    #+#                 */
/*   Updated: 2025/03/07 13:56:29 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/executer.h"

void handle_redirections(t_command *command)
{
    t_redirection *red_in;
    t_redirection *red_out;
    
    red_in = command->in;
    while (red_in)
	{
        int in_fd = open(red_in->file, O_RDONLY);
        if (in_fd == -1) {
            perror("Error opening input file");
            exit(EXIT_FAILURE);
        }
        dup2(in_fd, STDIN_FILENO); // Redirect stdin
        close(in_fd);
        red_in = red_in->next;
    }
    red_out = command->out;
    while (red_out)
	{
        int out_fd = open(red_out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fd == -1) {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }
        dup2(out_fd, STDOUT_FILENO); // Redirect stdout
        close(out_fd);
        red_out = red_out->next;
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
	t_command   *current;
    current = commands;
    
	while (current) 
	{
		execute_single_command(current);
		current = current->next;
	}
}
