/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/20 13:35:52 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/27 22:10:16 by sveta         ########   odam.nl         */
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

t_heredoc	prepare_heredoc_delimiter(char *raw_delimiter)
{
	t_heredoc	hd;
	size_t		len;

	hd.expand = 1;
	if (raw_delimiter[0] == '\'' || raw_delimiter[0] == '\"')
	{
		len = ft_strlen(raw_delimiter);
		if (len >= 2 && raw_delimiter[0] == raw_delimiter[len - 1])
		{
			hd.delimiter = ft_substr(raw_delimiter, 1, len - 2);
			hd.expand = 0;
		}
		else
			hd.delimiter = ft_strdup(raw_delimiter);
	}
	else
		hd.delimiter = ft_strdup(raw_delimiter);
	return (hd);
}

// Handles heredoc, setting up a pipe 
// and writing the input of the user into the PIPE.
int	read_heredoc(char *raw_delimiter, t_minishell *mshell)
{
	int			write_fd;
	int			read_fd;
	t_heredoc	hd;

	write_fd = setup_heredoc_pipe();
	if (write_fd == -1)
		return (-1);
	rl_event_hook = event;
	handle_signal(HEREDOC_SIG);
	hd = prepare_heredoc_delimiter(raw_delimiter);
	read_fd = process_heredoc_input(write_fd, &hd, mshell->envs);
	free(hd.delimiter);
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
			redir->fd = read_heredoc(redir->file, mshell);
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
