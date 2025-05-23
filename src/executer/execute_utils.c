/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 22:28:11 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/23 14:53:49 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	number_arguments(char **command_args)
{
	int	n;

	n = 0;
	while (command_args[n])
		n++;
	return (n);
}

void	set_or_update_env(t_minishell *mshell, char *var, char *value)
{
	t_env_node	*node;

	if (find_env_var(mshell->envs, var) == 0)
	{
		node = create_new_env_node(var, value);
		add_env_to_list(&(mshell->envs->env), node);
	}
	else
		change_env_var(mshell->envs, var, value);
}

// Initialises t_pipe_io, a struct which holds 
// the pipe read and write end was well as the previous read end.
// Used for chaining multiple commands
void	init_pipe_io(t_pipe_io *pipe_io)
{
	pipe_io->pipe_fd[0] = -1;
	pipe_io->pipe_fd[1] = -1;
	pipe_io->prev_read_end = STDIN_FILENO;
}

// Closes unused fd, and saves the prev_read_end of the pipe to share with
// the next command.
int	update_pipe_fd(t_pipe_io *pipe_io)
{
	close(pipe_io->pipe_fd[1]);
	if (pipe_io->prev_read_end != 0)
		close(pipe_io->prev_read_end);
	pipe_io->prev_read_end = dup(pipe_io->pipe_fd[0]);
	close(pipe_io->pipe_fd[0]);
	return (pipe_io->prev_read_end);
}

// Handles fd for the last child, closing the prev_read_end and rehabilitating
// STDIN
void	setup_last_child_io(int prev_read_end)
{
	dup2(prev_read_end, STDIN_FILENO);
	close(prev_read_end);
}
