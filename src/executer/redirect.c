/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:21:54 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/19 11:38:20 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

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

void	io_redirect(t_command *command)
{
	handle_input_redirections(command);
	handle_output_redirections(command);
}