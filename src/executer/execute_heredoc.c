/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/20 13:35:52 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/23 14:58:24 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

bool	set_all_heredocs(t_minishell *mshell)
{
	t_command	*cmd;

	cmd = mshell->commands;
	while (cmd)
	{
		handle_heredoc(mshell, &cmd);
		if (mshell->envs->status == 130)
			return (false);
		cmd = cmd->next;
	}
	return (true);
}

int	event(void)
{
	return (1);
}

// Handles heredoc, setting up a pipe 
// and writing the input of the user into the PIPE.
int	read_heredoc(char *delimiter)
{
	int		write_fd;
	int		read_fd;

	write_fd = setup_heredoc_pipe();
	if (write_fd == -1)
		return (-1);
	rl_event_hook = event;
	handle_signal(HEREDOC_SIG);
	read_fd = process_heredoc_input(write_fd, delimiter);
	handle_signal(MAIN_SIG);
	rl_on_new_line();
	rl_replace_line("", 0);
	return (read_fd);
}

// Checks if there is a heredoc to handle
void	handle_heredoc(t_minishell *mshell, t_command **command)
{
	t_redirection	*redir;

	redir = (*command)->in;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			redir->fd = read_heredoc(redir->file);
			if (redir->fd == -2)
			{
				mshell->envs->status = 130;
				return ;
			}
			if (redir->fd == -1)
			{
				perror("failed to set up heredoc\n");
				mshell->envs->status = 1;
				return ;
			}
		}
		redir = redir->next;
	}
}
