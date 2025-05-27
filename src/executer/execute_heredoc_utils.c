/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/20 13:35:52 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/27 13:17:15 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "env.h"

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

void	handle_heredoc_line(char *line, int write_fd, t_heredoc *hd, t_envs *envs)
{
	char *expanded;

	if (hd->expand && ft_strchr(line, '$'))
	{
		expanded = change_all_env(line, envs);
		if (expanded)
		{
			write_line_to_pipe(write_fd, expanded);
			free(line);
			return;
		}
	}
	write_line_to_pipe(write_fd, line);
}

// Prompts the user to write in STDIN
// Reads from STDIN until the delimiter
// Writes each line into the pipe
int	process_heredoc_input(int write_fd, t_heredoc *hd, t_envs *envs)
{
	char	*line;
	int		read_fd;

	read_fd = write_fd - 1;
	while (1)
	{
		if (g_signal_received)
		{
			g_signal_received = 0;
			close(write_fd);
			close(read_fd);
			return (-2);
		}
		line = readline("> ");
		if (!line || (ft_strncmp(line, hd->delimiter, ft_strlen(hd->delimiter)) == 0))
		{
			free(line);
			break ;
		}
		handle_heredoc_line(line, write_fd, hd, envs);
	}
	close(write_fd);
	return (read_fd);
}
