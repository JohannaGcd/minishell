/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 13:52:31 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/09 14:18:17 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "executer.h"

int	get_nbr_cmds(t_minishell *mshell)
{
	t_command *cmd;
	int nbr_cmds;

	nbr_cmds = 0;

	cmd = mshell->commands;
	while (cmd)
	{
		nbr_cmds += 1;
		cmd = cmd->next;
	}
	return (nbr_cmds);
}

int is_builtin_cmd(char **command_args)
{
	if (!command_args[0])
		return(0);
	if (ft_strncmp(command_args[0],"export", 7) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"env", 4) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"unset", 6) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"exit", 5) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"cd", 3) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"echo", 5) == 0)
		return (1);
	return (0);
}

void execute_commands(t_minishell *mshell, int *exit_status) 
{
	t_command   *current;
	char		**envp;
	char		*command_wp;

	current = mshell->commands;
	mshell->envs->status = 0;
	while (current)
	{  
		//printf("debug current command %s\n", current->command_args[0]);
		//printf("debug redir type %d and file %s\n", current->in->type, current->in->file); 
		if (current->command_args[0] && is_builtin_cmd(current->command_args))
			execute_builtin(current->command_args, mshell, exit_status);
		else if (current->next == NULL)
		{
			envp = envs_to_envp(mshell->envs);
			command_wp = return_command_with_path(current->command_args[0], mshell);
			//printf("command with path is %s\n", command_wp);
			if (command_wp)
				current->command_args[0] = command_wp;
			else
			{
				//printf("minishell: %s : command not found\n", current->command_args[0]);
				//perror
				mshell->envs->status = 127;
				return;
			}
			//printf("command with path =%s\n", current->command_args[0]);
			mshell->isExit = execute_single_command(mshell, current, envp);
			free_array(envp);
		}
		else
		{
			envp = envs_to_envp(mshell->envs);
			mshell->isExit = execute_multiple_cmd(envp, mshell);
			break;
		}
		current = current->next;
	}
}
