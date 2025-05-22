/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd_mul.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/18 17:51:53 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/22 18:12:05 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	setup_pipe(t_pipe_io *pipe_io)
{
	if (pipe(pipe_io->pipe_fd) == -1)
	{
		return (-1);
	}
	return (0);
}

pid_t	fork_child(t_minishell *mshell, t_command *curr_cmd,
			t_pipe_io *pipe_io, int *exit_status)
{
	pid_t	child_id;

	child_id = fork();
	if (child_id == 0)
	{
		handle_signal(CHILD_SIG);
		execute_child(mshell, curr_cmd, pipe_io, exit_status);
		handle_signal(PARENT_SIG);
	}
	return (child_id);
}

void	execute_pipeline(t_minishell *mshell, int *exit_status,
		int *nbr_children, t_pipe_io *pipe_io)
{
	t_command	*curr_cmd;
	pid_t		child_id;

	curr_cmd = mshell->commands;
	while (curr_cmd->next != NULL)
	{
		(*nbr_children)++;
		if (setup_pipe(pipe_io) == -1 || fork_child(mshell, curr_cmd,
				pipe_io, exit_status) == -1)
		{
			mshell->envs->status = 1;
			return ;
		}
		update_pipe_fd(pipe_io);
		curr_cmd = curr_cmd->next;
	}
	child_id = execute_last_cmd(mshell, curr_cmd, pipe_io, exit_status);
	wait_for_children(mshell, child_id, *nbr_children);
}

int	execute_multiple_cmd(t_minishell *mshell, int *exit_status)
{
	int			nbr_children;
	t_pipe_io	*pipe_io;

	nbr_children = 0;
	pipe_io = malloc(sizeof(t_pipe_io) * 1);
	if (!pipe_io)
		return (1);
	init_pipe_io(pipe_io);
	if (!set_all_heredocs(mshell))
		return (1);
	execute_pipeline(mshell, exit_status, &nbr_children, pipe_io);
	free(pipe_io);
	return (0);
}
