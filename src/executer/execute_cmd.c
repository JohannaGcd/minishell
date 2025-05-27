/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/15 12:25:46 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/27 18:22:56 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

// Handles the actual execution of the command depending on the type
void	use_exec_or_builtin(t_command *cmd, t_minishell *mshell,
	char **envp, int *exit_status)
{
	if (!is_builtin_cmd(cmd->command_args))
	{
		if (execve(cmd->command_args[0], cmd->command_args, envp) == -1)
		{
			perror("execve failed");
			free_array(envp);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		execute_builtin(cmd->command_args, mshell, exit_status);
		free_array(envp);
		exit(EXIT_SUCCESS);
	}
}

// Execution of each child process: gets the envp, the command_path
// then handles the pipe fds and the redirections
// before calling the function to execute either builtin command or execve.
int	execute_child(t_minishell *mshell, t_command *curr_cmd,
	t_pipe_io *pipe_io, int *exit_status)
{
	char	**envp;

	envp = prep_env_and_path(mshell, curr_cmd);
	if (!envp && !is_builtin_cmd(curr_cmd->command_args))
		exit(EXIT_FAILURE);
	set_up_child_fds(pipe_io);
	if (io_redirect(curr_cmd, mshell) == 1)
	{
		mshell->envs->status = 1;
		exit(EXIT_FAILURE);
	}
	use_exec_or_builtin(curr_cmd, mshell, envp, exit_status);
	return (0);
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

int	execute_last_cmd(t_minishell *mshell, t_command *curr_cmd,
	t_pipe_io *pipe_io, int *exit_status)
{
	pid_t	child_id;
	char	*command_wp;
	char	**envp;

	envp = envs_to_envp(mshell->envs);
	child_id = fork();
	if (child_id < 0)
		return (perror("fork failed"), mshell->envs->status = 1, -1);
	if (child_id == 0)
	{
		handle_signal(CHILD_SIG);
		setup_last_child_io(pipe_io->prev_read_end);
		checker_io_redirect(curr_cmd, mshell);
		if (!is_builtin_cmd(curr_cmd->command_args))
		{
			command_wp = return_cmd_w_path(curr_cmd->command_args[0], mshell);
			execute_command(command_wp, curr_cmd->command_args, envp);
		}
		else
			handle_builtin(curr_cmd, mshell, exit_status);
	}
	handle_signal(PARENT_SIG);
	close(pipe_io->prev_read_end);
	free_array(envp);
	return (child_id);
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
