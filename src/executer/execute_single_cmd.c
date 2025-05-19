/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_single_cmd.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/15 12:27:55 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/19 11:54:42 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

char	**prep_env_and_path(t_minishell *mshell, t_command *current)
{
	char	**envp;
	char	*cmd_path;

	envp = envs_to_envp(mshell->envs);
	cmd_path = return_cmd_with_path(current->command_args[0], mshell);
	if (cmd_path)
		current->command_args[0] = cmd_path;
	else
	{
		mshell->envs->status = 127;
		ft_putendl_fd(" command not found", 2);
		free_array(envp);
		return (NULL);
	}
	return (envp);
}

void	execute_child_single_cmd(t_command *command, char **envp)
{
	io_redirect(command);
	if (execve(command->command_args[0], command->command_args, envp) == -1)
	{
		perror("execve failed");
		if (errno == ENOENT)
			exit(127);
		else
			exit(126);
	}
}

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

int	execute_single_command(t_minishell *mshell, t_command *command, char **envp)
{
	pid_t	pid;
	int		status;	

	if (!set_all_heredocs(mshell))
	{
		mshell->envs->status = 1;
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		mshell->envs->status = 1;
		return (perror("fork failed"), -1);
	}
	else if (pid == 0)
		execute_child_single_cmd(command, envp);
	else
		execute_parent_single_cmd(mshell, &status, pid);
	return (0);
}

int	execute_if_single_command(t_command *cmd, t_minishell *mshell)
{
	char	**envp;

	envp = prep_env_and_path(mshell, cmd);
	if (!envp)
		return (1);
	mshell->envs->status = execute_single_command(mshell, cmd, envp);
	free_array(envp);
	return (0);
}
