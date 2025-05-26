/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/19 21:32:27 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/26 18:27:46 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	exec_exit(char **command_args, t_minishell *mshell, int *exit_status)
{
	*exit_status = mshell->envs->status;
	if (command_args[1] && command_args[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		*exit_status = 1;
		mshell->is_exit = 1;
		return (1);
	}
	if (command_args[1])
	{
		if (ft_is_number(command_args[1]))
		{
			*exit_status = ft_atoi(command_args[1]);
			printf("%d", *exit_status);
		}
		else
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			*exit_status = 2;
		}
	}
	mshell->is_exit = 1;
	return (*exit_status);
}
