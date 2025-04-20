/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/20 13:35:52 by jguacide      #+#    #+#                 */
/*   Updated: 2025/04/20 17:00:57 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "executer.h"

// TODO: handle expansion 
// TODO: handle signals

void	read_heredoc(char *delimiter)
{
	// Create variables for a pipe and a child process
	int pipe_fd[2];
	pid_t pid;
	char text[128];
	char *line;

	// Create pipe
	if (pipe(pipe_fd) == -1) // TODO: handle error
		return (perror("Error with pipe in handle heredoc."));

	// Fork process
	pid = fork();
	if (pid == -1)
		return (perror("fork heredoc"));

	// In the child process
	// Close read end, child only writes
	// write data into pipe's write end
	// close write end of the pipe once donce
	// exit child
	if (pid == 0)
	{		
		
		while (1)
		{
			line = readline("heredoc> ");
			if (!line)
				break;
			if (strcmp(line, delimiter) == 0)
			{
				free(line);
				break;
			}
			printf("\nline is: %s\n", line);
			write(pipe_fd[1], line, ft_strlen(line));
			write(pipe_fd[1], "\n", 1);

		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	// Parent process
	// Close write end, parent only reads
	// Wait until child finishes to write
	// Read from the pipe's read end into a buffer
	else 
	{
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
		int len = read(pipe_fd[0], text, sizeof(text) - 1);
		if (len > 0)
		{
			text[len] = '\0';
			printf("\nParent received: %s", text);
		}
		close(pipe_fd[0]);
	}
}

void	handle_heredoc(t_command *command)
{
	if (command->in->type == HEREDOC)
	{
		read_heredoc(command->in->file);
	}
	printf("\ncommand_args[0]: %s, delim = %s", command->command_args[0], command->in->file);
}

// Executor → open the pipe, read the heredoc, hook it up via dup2(), then run the command.