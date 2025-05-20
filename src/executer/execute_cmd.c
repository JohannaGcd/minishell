/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/15 12:25:46 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/19 13:49:24 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	execute_child(t_minishell *mshell, t_command *curr_cmd,
	t_pipe_io *pipe_io, int *exit_status)
{
	char	*command_wp;
	char	**envp;

	envp = envs_to_envp(mshell->envs);
	close(pipe_io->pipe_fd[0]);
	dup2(pipe_io->prev_read_end, STDIN_FILENO);
	dup2(pipe_io->pipe_fd[1], STDOUT_FILENO);
	close(pipe_io->pipe_fd[1]);
	io_redirect(curr_cmd);
	if (!is_builtin_cmd(curr_cmd->command_args))
	{
		command_wp = return_cmd_with_path(curr_cmd->command_args[0], mshell);
		if (execve(command_wp, curr_cmd->command_args, envp) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		execute_builtin(curr_cmd->command_args, mshell, exit_status);
		exit(EXIT_SUCCESS);
	}
	free_array(envp);
	return (0);
}
//---------

void	setup_last_child_io(int prev_read_end)
{
	dup2(prev_read_end, STDIN_FILENO);
	close(prev_read_end);
}

void	execute_command(char *command_wp, char **command_args, char **envp)
{
	if (execve(command_wp, command_args, envp) == -1)
	{
		perror("execve failed");
		if (errno == ENOENT)
		{
			exit(127);
		}
		else
		{
			exit(126);
		}
	}
}

void	handle_builtin(t_command *curr_cmd, t_minishell *mshell, int *exit_status)
{
	execute_builtin(curr_cmd->command_args, mshell, exit_status);
	exit(EXIT_SUCCESS);
}

int	execute_last_cmd(t_minishell *mshell, t_command *curr_cmd, t_pipe_io *pipe_io, int *exit_status)
{
	pid_t	child_id;
	char	*command_wp;
	char	**envp;

	envp = envs_to_envp(mshell->envs);
	child_id = fork();
	if (child_id < 0)
	{
		perror("fork failed");
		mshell->envs->status = 1;
		return (-1);
	}
	if (child_id == 0)
	{
		setup_last_child_io(pipe_io->prev_read_end);
		io_redirect(curr_cmd);
		if (!is_builtin_cmd(curr_cmd->command_args))
		{
			command_wp = return_cmd_with_path(curr_cmd->command_args[0], mshell);
			execute_command(command_wp, curr_cmd->command_args, envp);
		}
		else
			handle_builtin(curr_cmd, mshell, exit_status);
	}
	close(pipe_io->prev_read_end);
	free_array(envp);
	return (child_id);
}
// int	execute_last_cmd(t_minishell *mshell, t_command *curr_cmd, char **envp,
// 	int prev_read_end, int *exit_status)
// {
// 	pid_t	child_id;
// 	char	*command_wp;

// 	child_id = fork();
// 	if (child_id < 0)
// 	{
// 		perror("fork did not work in execute_last_cmd");
// 		mshell->envs->status = 1;
// 		return (-1);
// 	}
// 	if (child_id == 0)
// 	{
// 		dup2(prev_read_end, STDIN_FILENO);
// 		close(prev_read_end);
// 		io_redirect(curr_cmd);
// 		if (!is_builtin_cmd(curr_cmd->command_args))
// 		{
// 			command_wp = return_cmd_with_path(curr_cmd->command_args[0],
// 					mshell);
// 			if (execve(command_wp, curr_cmd->command_args, envp) == -1)
// 			{
// 				perror("execve failed");
// 				if (errno == ENOENT)
// 					exit(127);
// 				else
// 					exit(126);
// 			}
// 		}
// 		else
// 		{
// 			execute_builtin(curr_cmd->command_args, mshell, exit_status);
// 			exit(EXIT_SUCCESS);
// 		}
// 	}
// 	close(prev_read_end);
// 	return (child_id);
// }

int	update_pipe_fd(t_pipe_io *pipe_io)
{
	close(pipe_io->pipe_fd[1]);
	if (pipe_io->prev_read_end != 0)
		close(pipe_io->prev_read_end);
	pipe_io->prev_read_end = dup(pipe_io->pipe_fd[0]);
	close(pipe_io->pipe_fd[0]);
	return (pipe_io->prev_read_end);
}

void	wait_for_children(t_minishell *mshell, pid_t child_id, int nbr_children)
{
	int	status;

	if (waitpid(child_id, &status, 0) < 0)
	{
		perror("waitpid error");
		mshell->envs->status = 1;
	}
	else
	{
		if (WIFEXITED(status))
			mshell->envs->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			mshell->envs->status = 128 + WTERMSIG(status);
		else
			mshell->envs->status = 1;
	}
	while (nbr_children > 0)
	{
		wait(NULL);
		nbr_children--;
	}
}
