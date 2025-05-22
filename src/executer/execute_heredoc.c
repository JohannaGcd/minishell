/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/20 13:35:52 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/22 13:51:19 by spanfilo      ########   odam.nl         */
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
int event(void)
{	
	return (1);
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
	rl_event_hook = event;
	handle_signal(HEREDOC_SIG);
	while (1)
	{
		if (g_signal_received)
		{
			//g_signal_received = 0;
			break;  
		}

		//rl_catch_signals = 0;
		line = readline("> ");
		//printf("line: %s\n", line);
		if (!line || (strcmp(line, delimiter) == 0))
		{
			free(line);
			break ;
		}
		//printf("HH\n");
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	handle_signal(PARENT_SIG);
	close(pipe_fd[1]);
	if (g_signal_received )
	{
		g_signal_received = 0;
		close(pipe_fd[0]);
		//printf("HERE2.1\n");
		//return (-2);
		return (-2);
	}
	else
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
			//write(1,"HERE3\n",6);
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

// After the heredoc, checks whether it is not an empty command
// before execve.
// int	check_if_valid_command(t_minishell *mshell)
// {
// 	if (mshell->commands->command_args[0])


// }