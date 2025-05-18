/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd_mul.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/18 17:51:53 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/18 18:04:00 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	setup_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		return (-1);
	}
	return (0);
}

pid_t	fork_child(t_minishell *mshell, t_command *curr_cmd, char **envp, int *pipe_fd, int prev_read_end, int *exit_status)
{
	pid_t	child_id;

	child_id = fork();
	if (child_id == 0)
	{
		execute_child(mshell, curr_cmd, envp, pipe_fd, prev_read_end, exit_status);
	}
	return (child_id);
}

void	execute_pipeline(t_minishell *mshell, char **envp, int *exit_status, int *nbr_children, int *prev_read_end)
{
	t_command	*curr_cmd;
	int			pipe_fd[2];
	pid_t		child_id;

	curr_cmd = mshell->commands;
	while (curr_cmd->next != NULL)
	{
		(*nbr_children)++;
		if (setup_pipe(pipe_fd) == -1 || fork_child(mshell, curr_cmd, envp, pipe_fd, *prev_read_end, exit_status) == -1)
		{
			mshell->envs->status = 1;
			return ;
		}
		*prev_read_end = update_pipe_fd(pipe_fd, *prev_read_end);
		curr_cmd = curr_cmd->next;
	}
	child_id = execute_last_cmd(mshell, curr_cmd, envp, *prev_read_end, exit_status);
	wait_for_children(mshell, child_id, *nbr_children);
}

int	execute_multiple_cmd(char **envp, t_minishell *mshell, int *exit_status)
{
	int	nbr_children;
	int	prev_read_end;

	nbr_children = 0;
	prev_read_end = STDIN_FILENO;
	if (!set_all_heredocs(mshell))
	{
		return (1);
	}
	execute_pipeline(mshell, envp, exit_status, &nbr_children, &prev_read_end);
	return (0);
}

// int	execute_multiple_cmd(char **envp, t_minishell *mshell, int *exit_status)
// {
// 	t_command	*curr_cmd;
// 	int			pipe_fd[2];
// 	int			nbr_children;
// 	pid_t		child_id;
// 	int			prev_read_end;

// 	curr_cmd = mshell->commands;
// 	prev_read_end = STDIN_FILENO;
// 	nbr_children = 0;
// 	if (!set_all_heredocs(mshell))
// 		return (1);
// 	while (curr_cmd->next != NULL)
// 	{
// 		nbr_children++;
// 		if (pipe(pipe_fd) == -1)
// 		{
// 			mshell->envs->status = 1;
// 			return (-1);
// 		}
// 		child_id = fork();
// 		if (child_id == -1)
// 		{
// 			mshell->envs->status = 1;
// 			return (-1);
// 		}
// 		if (child_id == 0)
// 			execute_child(mshell, curr_cmd, envp, pipe_fd, 
//				prev_read_end, exit_status);
// 		prev_read_end = update_pipe_fd(pipe_fd, prev_read_end);
// 		curr_cmd = curr_cmd->next;
// 	}
// 	child_id = execute_last_cmd(mshell, curr_cmd, envp,
//	prev_read_end, exit_status);
// 	wait_for_children(mshell, child_id, nbr_children);
// 	mshell->envs->status = mshell->envs->status;
// 	return (0);
// }