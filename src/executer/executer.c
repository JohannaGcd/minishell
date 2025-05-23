/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 13:52:31 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/23 12:17:55 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

// Count the number of commands
int	get_nbr_cmds(t_minishell *mshell)
{
	t_command	*cmd;
	int			nbr_cmds;

	nbr_cmds = 0;
	cmd = mshell->commands;
	while (cmd)
	{
		nbr_cmds += 1;
		cmd = cmd->next;
	}
	return (nbr_cmds);
}

// Check if it is a built-in command.
int	is_builtin_cmd(char **command_args)
{
	if (!command_args[0])
		return (0);
	if (ft_strncmp(command_args[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(command_args[0], "env", 4) == 0)
		return (1);
	if (ft_strncmp(command_args[0], "unset", 6) == 0)
		return (1);
	if (ft_strncmp(command_args[0], "exit", 5) == 0)
		return (1);
	if (ft_strncmp(command_args[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(command_args[0], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(command_args[0], "pwd", 4) == 0)
		return (1);
	return (0);
}

// Decides which case to apply: execute as a single command: built-in or not
// or multiple commands.
void	execute_commands(t_minishell *mshell, int *exit_status)
{
	t_command	*current;

	current = mshell->commands;
	while (current)
	{
		if (current->command_args[0] && is_builtin_cmd(current->command_args)
			&& current->next == NULL)
			redirect_for_builtin(current, mshell, exit_status);
		else if (current->next == NULL)
		{
			if (execute_if_single_command(current, mshell))
				return ;
		}
		else
		{
			mshell->envs->status = execute_multiple_cmd(mshell,
					exit_status);
			break ;
		}
		current = current->next;
	}
}
