/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/15 12:25:46 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/15 14:52:51 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	execute_child(t_minishell *mshell, t_command *curr_cmd, char **envp,
	int *pipe_fd, int prev_read_end, int *exit_status)
{
	char	*command_wp;

	close(pipe_fd[0]);
	dup2(prev_read_end, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
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
	return (0);
}

int	execute_last_cmd(t_minishell *mshell, t_command *curr_cmd, char **envp,
	int prev_read_end, int *exit_status)
{
	pid_t	child_id;
	char	*command_wp;

	child_id = fork();
	if (child_id < 0)
	{
		perror("fork did not work in execute_last_cmd");
		mshell->envs->status = 1;
		return (-1);
	}
	if (child_id == 0)
	{
		dup2(prev_read_end, STDIN_FILENO);
		close(prev_read_end);
		io_redirect(curr_cmd);
		if (!is_builtin_cmd(curr_cmd->command_args))
		{
			command_wp = return_cmd_with_path(curr_cmd->command_args[0],
					mshell);
			if (execve(command_wp, curr_cmd->command_args, envp) == -1)
			{
				perror("execve failed");
				if (errno == ENOENT)
					exit(127);
				else
					exit(126);
			}
		}
		else
		{
			execute_builtin(curr_cmd->command_args, mshell, exit_status);
			exit(EXIT_SUCCESS);
		}
	}
	close(prev_read_end);
	return (child_id);
}

int	update_pipe_fd(int *pipe_fd, int prev_read_end)
{
	close(pipe_fd[1]);
	if (prev_read_end != 0)
		close(prev_read_end);
	prev_read_end = dup(pipe_fd[0]);
	close(pipe_fd[0]);
	return (prev_read_end);
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

int	execute_multiple_cmd(char **envp, t_minishell *mshell, int *exit_status)
{
	t_command	*curr_cmd;
	int			pipe_fd[2];
	int			nbr_children;
	pid_t		child_id;
	int			prev_read_end;

	curr_cmd = mshell->commands;
	prev_read_end = STDIN_FILENO;
	nbr_children = 0;
	if (!set_all_heredocs(mshell))
		return (1);
	while (curr_cmd->next != NULL)
	{
		nbr_children++;
		if (pipe(pipe_fd) == -1)
		{
			mshell->envs->status = 1;
			return (-1);
		}
		child_id = fork();
		if (child_id == -1)
		{
			mshell->envs->status = 1;
			return (-1);
		}
		if (child_id == 0)
			execute_child(mshell, curr_cmd, envp, pipe_fd, prev_read_end, exit_status);
		prev_read_end = update_pipe_fd(pipe_fd, prev_read_end);
		curr_cmd = curr_cmd->next;
	}
	child_id = execute_last_cmd(mshell, curr_cmd, envp, prev_read_end, exit_status);
	wait_for_children(mshell, child_id, nbr_children);
	mshell->envs->status = mshell->envs->status;
	return (0);
}
