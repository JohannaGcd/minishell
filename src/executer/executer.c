/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 13:52:31 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/15 09:44:19 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

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
	return (0);
}

void	execute_commands(t_minishell *mshell, int *exit_status)
{
	t_command	*current;
	char		**envp;
	char		*com_wp;

	current = mshell->commands;
	while (current)
	{
		if (current->command_args[0] && is_builtin_cmd(current->command_args)
			&& current->next == NULL)
		{
			io_redirect(current);
			execute_builtin(current->command_args, mshell, exit_status);
		}
		else if (current->next == NULL)
		{
			envp = envs_to_envp(mshell->envs);
			com_wp = return_command_with_path(current->command_args[0], mshell);
			if (com_wp)
				current->command_args[0] = com_wp;
			else
			{
				perror("command not found");
				mshell->envs->status = 127;
				return ;
			}
			mshell->envs->status = execute_single_command(mshell,
					current, envp);
			free_array(envp);
		}
		else
		{
			envp = envs_to_envp(mshell->envs);
			mshell->envs->status = execute_multiple_cmd(envp, mshell,
					exit_status);
			break ;
		}
		current = current->next;
	}
}

//debugging
// if(current->in)
// 	printf("debug current command file: %s, and type %d\n",
//current->in->file, current->in->type);
// if(current->out)
// 	printf("debug current command file: %s, and type %d\n", 
//current->out->file, current->out->type);