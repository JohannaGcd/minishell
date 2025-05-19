/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/20 13:35:52 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/19 13:58:44 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "minishell.h" 

bool	set_all_heredocs(t_minishell *mshell)
{
	t_command	*cmd;

	cmd = mshell->commands;
	while (cmd)
	{
		handle_heredoc(mshell, &cmd);
		if (mshell->isExit != 0)
			return (false);
		cmd = cmd->next;
	}
	return (true);
}

// TODO: add a check if delimiter is empty
int	read_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error with pipe in handle heredoc.");
		return (-1);
	}
	handle_signal(HEREDOC_SIG);
	while (1)
	{
		if (signal_received)
		{
            signal_received = 0;  
            break;  
        }
		line = readline("heredoc> ");
		if (!line || (strcmp(line, delimiter) == 0))
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	handle_heredoc(t_minishell *mshell, t_command **command)
{
	t_redirection	*redir;

	redir = (*command)->in;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			redir->fd = read_heredoc(redir->file);
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
