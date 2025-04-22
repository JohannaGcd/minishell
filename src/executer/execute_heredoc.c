/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/20 13:35:52 by jguacide      #+#    #+#                 */
/*   Updated: 2025/04/22 14:45:24 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "executer.h"

// TODO: handle expansion 
// TODO: handle signals

int	read_heredoc(char *delimiter)
{
	int pipe_fd[2];
	char *line;

	// Create pipe
	if (pipe(pipe_fd) == -1)
	{
		perror("Error with pipe in handle heredoc.");
		return -1;
	}

	while (1)
	{
		line = readline("heredoc> ");
		if (!line || (strcmp(line, delimiter) == 0))
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]); 

	return pipe_fd[0]; // return read-end of the pipe
}

void	handle_heredoc(t_command **command)
{
	if ((*command)->in)
	{
		while ((*command)->in)
		{
			if ((*command)->in->type == HEREDOC)
			{
				(*command)->in->fd = read_heredoc((*command)->in->file);
				if ((*command)->in->fd == -1)
				{
					perror("failed to set up heredoc\n");
					exit(EXIT_FAILURE);
				}
				break; // only handle the first heredoc for now
			}
		}
	}
}