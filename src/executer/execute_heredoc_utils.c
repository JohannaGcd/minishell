/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/20 13:35:52 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/23 14:57:21 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

// Writes the lines imputed from STDIN into the pipe for the heredoc
void	write_line_to_pipe(int pipe_fd, char *line)
{
	write(pipe_fd, line, ft_strlen(line));
	write(pipe_fd, "\n", 1);
	free(line);
}

// Initialises a pipe for the heredoc
int	setup_heredoc_pipe(void)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("Error with pipe in handle heredoc.");
		return (-1);
	}
	return (pipe_fd[1]);
}

// Prompts the user to write in STDIN
// Reads from STDIN until the delimiter
// Writes each line into the pipe
int	process_heredoc_input(int write_fd, char *delimiter)
{
	char	*line;
	int		read_fd;

	read_fd = write_fd - 1;
	while (1)
	{
		if (g_signal_received)
			break ;
		line = readline("> ");
		if (!line || (strcmp(line, delimiter) == 0))
		{
			free(line);
			break ;
		}
		write_line_to_pipe(write_fd, line);
	}
	close(write_fd);
	if (g_signal_received)
	{
		g_signal_received = 0;
		close(read_fd);
		return (-2);
	}
	return (read_fd);
}
