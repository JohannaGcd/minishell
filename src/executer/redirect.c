/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:21:54 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/23 14:48:50 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

// Handles input redirections
void	handle_input_redirections(t_command *command)
{
	t_redirection	*red_in;

	red_in = command->in;
	while (red_in)
	{
		if (red_in->type != HEREDOC)
		{
			red_in->fd = open(red_in->file, O_RDONLY);
			if (red_in->fd == -1)
				return (perror("Error opening input file"), exit(EXIT_FAILURE));
		}
		dup2(command->in->fd, STDIN_FILENO);
		close(command->in->fd);
		red_in = red_in->next;
	}
}

// Handles output redirection
void	handle_output_redirections(t_command *command)
{
	t_redirection	*red_out;
	int				out_fd;

	red_out = command->out;
	while (red_out)
	{
		if (red_out->type == APPEND)
			out_fd = open(red_out->file, O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			out_fd = open(red_out->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (out_fd == -1)
		{
			perror("Error opening output file");
			exit(EXIT_FAILURE);
		}
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
		red_out = red_out->next;
	}
}

// Launches the appropriate redirection function depending on its type
void	io_redirect(t_command *command)
{
	handle_input_redirections(command);
	handle_output_redirections(command);
}

// Handles fd for the pipes, for multiple commands specifically.
void	set_up_child_fds(t_pipe_io *pipe_io)
{
	close(pipe_io->pipe_fd[0]);
	dup2(pipe_io->prev_read_end, STDIN_FILENO);
	dup2(pipe_io->pipe_fd[1], STDOUT_FILENO);
	close(pipe_io->pipe_fd[1]);
}
