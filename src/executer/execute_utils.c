/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 22:28:11 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/22 15:02:56 by jguacide      ########   odam.nl         */
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

void	init_pipe_io(t_pipe_io *pipe_io)
{
	pipe_io->pipe_fd[0] = -1;
	pipe_io->pipe_fd[1] = -1;
	pipe_io->prev_read_end = STDIN_FILENO;
}

int	update_pipe_fd(t_pipe_io *pipe_io)
{
	close(pipe_io->pipe_fd[1]);
	if (pipe_io->prev_read_end != 0)
		close(pipe_io->prev_read_end);
	pipe_io->prev_read_end = dup(pipe_io->pipe_fd[0]);
	close(pipe_io->pipe_fd[0]);
	return (pipe_io->prev_read_end);
}

void	setup_last_child_io(int prev_read_end)
{
	dup2(prev_read_end, STDIN_FILENO);
	close(prev_read_end);
}
