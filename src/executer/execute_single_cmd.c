/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_single_cmd.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/15 12:27:55 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/29 12:47:47 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

// Returns the envp and replaced the command stored in command_args[0]
// with the appropriate executable path.
char	**prep_env_and_path(t_minishell *mshell, t_command *current)
{
	char	**envp;
	char	*cmd_path;

	envp = envs_to_envp(mshell->envs);
	if (current->command_args[0] == NULL)
	{
		free_array(envp);
		return (NULL);
	}
	cmd_path = return_cmd_w_path(current->command_args[0], mshell);
	if (cmd_path)
	{
		free(current->command_args[0]);
		current->command_args[0] = cmd_path;
	}
	else
	{
		mshell->envs->status = 127;
		ft_putendl_fd(" command not found", 2);
		free_array(envp);
		return (NULL);
	}
	return (envp);
}

// Handles redirections and launches execve.
void	execute_child_single_cmd(t_command *command, char **envp,
		t_minishell *mshell)
{
	if (io_redirect(command, mshell) == 1)
	{
		mshell->envs->status = 1;
		exit(EXIT_FAILURE);
	}
	if (execve(command->command_args[0], command->command_args, envp) == -1)
	{
		perror("execve failed");
		if (errno == ENOENT)
			exit(127);
		else
			exit(126);
	}
}

// Parent process waits for the execution of the child process
// and retrieves the exit status.
void	execute_parent_single_cmd(t_minishell *mshell, int *status, int pid)
{
	mshell->envs->status = 0;
	if (waitpid(pid, status, 0) == -1)
		mshell->envs->status = 1;
	else
	{
		if (WIFEXITED(*status))
			mshell->envs->status = WEXITSTATUS(*status);
		else if (WIFSIGNALED(*status))
			mshell->envs->status = 128 + WTERMSIG(*status);
		else
			mshell->envs->status = 1;
	}
}

// Triggers the execution of the single command in the child process
// and the handling by the parent.
int	execute_single_command(t_minishell *mshell, t_command *command, char **envp)
{
	pid_t	pid;
	int		status;	

	// if (!set_all_heredocs(mshell))
	// 	return (mshell->envs->status = 130, 130);
	if (command->in && command->in->fd == -2)
	{
		mshell->envs->status = 130;
		return (130);
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), mshell->envs->status = 1, -1);
	else if (pid == 0)
	{
		handle_signal(CHILD_SIG);
		execute_child_single_cmd(command, envp, mshell);
		handle_signal(PARENT_SIG);
	}
	else
	{
		handle_signal(PARENT_SIG);
		execute_parent_single_cmd(mshell, &status, pid);
	}
	return (mshell->envs->status);
}

// Gets the envp and triggers the execution of the command.
int	execute_if_single_command(t_command *cmd, t_minishell *mshell)
{
	char	**envp;

	if (!set_all_heredocs(mshell))
		return (mshell->envs->status = 130, 130);
	envp = prep_env_and_path(mshell, cmd);
	if (!envp)
		return (1);
	mshell->envs->status = execute_single_command(mshell, cmd, envp);
	free_array(envp);
	return (0);
}
